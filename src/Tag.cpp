// BSD 3-Clause License

// Copyright (c) 2020, Andreas Tzomakas
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#include "Tag.h"

#include <iostream>
#include <algorithm>

using namespace std;



namespace htmlCplusplus
{

#ifdef TRACE_POINTERS    
    std::set<uintptr_t> * Tag::s_htmlTags = new std::set<uintptr_t>();
#endif

    Tag::Tag()
    {
        m_ostream = &std::wcout;

        m_name = "";
        m_content = L"";

        m_closeTag = true;
    }

    Tag::Tag(std::wostream &ostr)
    {
        m_ostream = &ostr;
        m_name = "";
        m_content = L"";

        m_closeTag = true;
    }

    Tag::Tag(string name, bool closeTag)
	{
        m_ostream = &std::wcout;
		m_name = HtmlString::RemoveInvalid(name);
        m_content = L"";

        m_closeTag = closeTag;
	}

	Tag::Tag(string name, string content, bool escapeChars, bool closeTag)
	{
        m_ostream = &std::wcout;
		m_name = HtmlString::RemoveInvalid(name);

        if (escapeChars)
            m_content = HtmlString::Escape(HtmlString::ToWString(content));
        else
            m_content = HtmlString::ToWString(content);

        m_closeTag = closeTag;
	}

	Tag::Tag(string name, wstring content, bool escapeChars, bool closeTag)
	{
        m_ostream = &std::wcout;
		m_name = HtmlString::RemoveInvalid(name);

        if (escapeChars)
            m_content = HtmlString::Escape(content);
        else
            m_content.assign(content);

        m_closeTag = closeTag;
	}

    void Tag::SetStream(std::wostream &ostr)
    {
        m_ostream = &ostr;

        if (m_otherTags.size() > 0)
        {
            for (std::list<Tag *>::iterator iter = m_otherTags.begin(); iter != m_otherTags.end(); iter++)
            {
                (*iter)->SetStream(ostr);
            }
        }
    }

    void Tag::SetBeautifier(IHtmlBeautify *beautify)
    {
        m_Beautify = beautify;

        if (m_otherTags.size() > 0)
        {
            for (std::list<Tag *>::iterator iter = m_otherTags.begin(); iter != m_otherTags.end(); iter++)
            {
                (*iter)->SetBeautifier(m_Beautify);
            }
        }
    }

    void Tag::SetName(string name, bool closeTag)
    {
        m_name = HtmlString::RemoveInvalid(name);
        m_closeTag = closeTag;
    }

    void Tag::SetContent(string content, bool escapeChars)
    {
        SetContent(HtmlString::ToWString(content), escapeChars);
    }

    void Tag::SetContent(wstring content, bool escapeChars)
    {
        if (escapeChars)
            m_content = HtmlString::Escape(content);
        else
            m_content.assign(content);
    }

    void Tag::SetContentNewLines(bool prefixNewLine, bool suffixNewLine)
    {
        m_ContentPrefixNewLine = prefixNewLine;
        m_ContentSuffixNewLine = suffixNewLine;
    }
 
    void Tag::AddAttribute(string name, string content, bool escapeChars)
    {
        AddAttribute(name, HtmlString::ToWString(content), escapeChars);
    }

    void Tag::AddAttribute(string name, wstring content, bool escapeChars)
    {
        if (escapeChars)
            m_properties.insert(std::pair<string, wstring>(HtmlString::RemoveInvalid(name), HtmlString::Escape(content)));
        else
            m_properties.insert(std::pair<string, wstring>(HtmlString::RemoveInvalid(name), content));
    }

    void Tag::ClearAttributes()
    {
        m_properties.clear();
    }


    void Tag::AddTag(Tag *tag)
    {
        if (tag != NULL)
        {
            tag->SetStream(*m_ostream);
            tag->SetBeautifier(m_Beautify);

            m_otherTags.push_back(tag);
        }
    }

    void Tag::AddTag(string name, string content, bool escapeChars, bool closeTag)
    {
        AddTag(name, HtmlString::ToWString(content), escapeChars, closeTag);
    }

    void Tag::AddTag(string name, wstring content, bool escapeChars, bool closeTag)
    {
        Tag *tag = new Tag(name, content, escapeChars, closeTag);

        tag->SetStream(*m_ostream);
        tag->SetBeautifier(m_Beautify);

        m_otherTags.push_back(tag); 
    }


    void Tag::Render(Identation identation)
    {
        if (m_Beautify != NULL)
            m_Beautify->RenderIdentation(m_ostream, identation);

        (*m_ostream) << L"<" << HtmlString::ToWString(m_name);

        std::map<string, wstring>::iterator iter = m_properties.begin();

        while (iter != m_properties.end())
        {
            (*m_ostream) << L" " << HtmlString::ToWString(iter->first) << L"=\"";
            (*m_ostream) << iter->second;
            (*m_ostream) << L"\"";

            iter++;
        } 

        (*m_ostream) << L">";

        if (m_otherTags.size() > 0)
        {
            for (std::list<Tag *>::iterator iter = m_otherTags.begin(); iter != m_otherTags.end(); iter++)
            {
                (*iter)->Render((Identation) { identation.Ident, identation.IdentNumber, identation.Level + 1 }); 
            }
        }

        if (m_content.length() > 0)
        {
            if ((m_ContentPrefixNewLine) || (m_ContentSuffixNewLine))
            {
                if (m_ContentPrefixNewLine)
                    (*m_ostream) << std::endl; 

                (*m_ostream) << m_content;

                if (m_ContentSuffixNewLine)
                    (*m_ostream) << std::endl;

                if (m_Beautify != NULL)
                    m_Beautify->RenderIdentation(m_ostream, identation);

            }
            else
                (*m_ostream) << m_content;
        }
        else 
        {
            if (m_Beautify != NULL)
                m_Beautify->RenderIdentation(m_ostream, identation);
        }

        if (m_closeTag)
            (*m_ostream) << L"</" << HtmlString::ToWString(m_name) << L">";

        (*m_ostream).flush();
    }

	Tag::~Tag()
	{
        for(std::list<Tag *>::iterator iter = m_otherTags.begin(); iter != m_otherTags.end(); iter++)
        {
            (*iter)->Dispose();
        }

        m_otherTags.clear();
        m_properties.clear();
	}

    void Tag::Dispose()
    {
        if (!m_Disposed) 
        {
            m_Disposed = false;

            delete this;
        }
    }



#ifdef TRACE_POINTERS

            void * Tag::operator new(size_t size)
            {
                Tag *newObj = ::new Tag();

                uintptr_t addr = reinterpret_cast<uintptr_t>(newObj);

                s_htmlTags->insert(addr);

                return newObj;
            }

            void * Tag::operator new(size_t size, std::wostream &ostr)
            {
                Tag *newObj = ::new Tag(ostr);

                uintptr_t addr = reinterpret_cast<uintptr_t>(newObj);

                s_htmlTags->insert(addr);

                return newObj;
            }


            void * Tag::operator new[](size_t size, std::wostream &ostr)
            {
                Tag *newObj = ::new Tag[size];

                uintptr_t addr = reinterpret_cast<uintptr_t>(newObj);

                for (int idx = 0; idx < size; idx++)
                    newObj[idx].SetStream(ostr);

                s_htmlTags->insert(addr);

                return newObj;
            }


            void Tag::operator delete(void *p)
            {
                uintptr_t addr = reinterpret_cast<uintptr_t>(p);
                std::set<uintptr_t>::iterator it = s_htmlTags->find(addr);

                if (it != s_htmlTags->end())
                {
                    ::operator delete(p);

                    s_htmlTags->erase(it);
                }

            }

            void Tag::operator delete[](void *p)
            {
                uintptr_t addr = reinterpret_cast<uintptr_t>(p);
                std::set<uintptr_t>::iterator it = s_htmlTags->find(addr);

                if (it != s_htmlTags->end())
                {
                    ::operator delete[](p);
                    
                    s_htmlTags->erase(it);
                }
            }

            std::size_t Tag::TagsCount()
            {
                size_t count = s_htmlTags->size();

                return count;
            }
#endif


}

