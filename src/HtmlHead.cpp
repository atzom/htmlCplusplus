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

#include "HtmlHead.h"
#include "HtmlString.h"
#include "Tag.h"

namespace htmlCplusplus
{
    HtmlHead::HtmlHead(std::wostream &stream)
    {
        m_ostream = &stream;
    }

    HtmlHead::~HtmlHead()
    {
        std::map<std::string, htmlCplusplus::Tag *>::iterator iter = m_tags.begin();

        while (iter != m_tags.end())
        {
            iter->second->Dispose();

            iter++;
        }

        m_tags.clear();
    }

    void HtmlHead::SetStream(std::wostream &ostr)
    {
        m_ostream = &ostr;
    }

    void HtmlHead::SetBeautifier(IHtmlBeautify *beautify)
    {
        m_Beautify = beautify;
    }

    void HtmlHead::RenderIdentation(std::wostream *ostr, Identation identation)
    {
        if (m_Beautify)
            m_Beautify->RenderIdentation(ostr, identation);
    }

    void HtmlHead::SetTitle(std::wstring title)
    {
        std::map<std::string, Tag *>::iterator iter = m_tags.find("title");

        if (iter != m_tags.end())
        {
            iter->second->SetContent(title, true);
        }
        else
        {
            Tag *tag = new Tag("title", title, true);

            tag->SetStream(*m_ostream);
            tag->SetBeautifier(m_Beautify);

            m_tags.insert(std::pair<std::string, Tag *>("title", tag));
        }
    }

    void HtmlHead::SetBase(std::map<std::string, std::wstring> attributes)
    {
        std::map<std::string, Tag *>::iterator iter = m_tags.find("base");
        Tag *tag;

        if (iter != m_tags.end())
        {
            tag = iter->second;
        }
        else
        {
            Tag *tag = new Tag("base");

            tag->SetStream(*m_ostream);
            tag->SetBeautifier(m_Beautify);

            m_tags.insert(std::pair<std::string, Tag *>("base", tag));
        }

        for (std::map<std::string, std::wstring>::const_iterator attrIter = attributes.begin(); attrIter != attributes.end(); attrIter++)
        {
            tag->AddAttribute(attrIter->first, attrIter->second, true);
        }
    }

    void HtmlHead::AddStyle(std::wstring style)
    {
        Tag *tag = new Tag("style", style, false);

        tag->SetStream(*m_ostream);
        tag->SetBeautifier(m_Beautify);

        m_tags.insert(std::pair<std::string, htmlCplusplus::Tag *>("style#" + std::to_string(m_tags.size()), tag));
    }

    void HtmlHead::AddScript(std::wstring script)
    {
        Tag *tag = new Tag("script", script, false);

        tag->SetStream(*m_ostream);
        tag->SetBeautifier(m_Beautify);

        m_tags.insert(std::pair<std::string, htmlCplusplus::Tag *>("script#" + std::to_string(m_tags.size()), tag));
    }

    void HtmlHead::AddLink(std::map<std::string, std::wstring> attributes)
    {
        Tag *tag = new Tag("link");

        tag->SetStream(*m_ostream);
        tag->SetBeautifier(m_Beautify);

        for (std::map<std::string, std::wstring>::const_iterator attrIter = attributes.begin(); attrIter != attributes.end(); attrIter++)
        {
            tag->AddAttribute(attrIter->first, attrIter->second, false);
        }

        m_tags.insert(std::pair<std::string, htmlCplusplus::Tag *>("link#" + std::to_string(m_tags.size()), tag));
    }

    void HtmlHead::AddMeta(std::map<std::string, std::wstring> attributes)
    {
        Tag *tag = new Tag("meta", false);

        tag->SetStream(*m_ostream);
        tag->SetBeautifier(m_Beautify);

        for (std::map<std::string, std::wstring>::const_iterator attrIter = attributes.begin(); attrIter != attributes.end(); attrIter++)
        {
            tag->AddAttribute(attrIter->first, attrIter->second, false);
        }

        m_tags.insert(std::pair<std::string, htmlCplusplus::Tag *>("meta#" + std::to_string(m_tags.size()), tag));
    }

    void HtmlHead::Render(Identation identation)
    {
        std::map<std::string, htmlCplusplus::Tag *>::iterator iter = m_tags.begin();

        RenderIdentation(m_ostream, identation);
        (*m_ostream) << L"<head>";

        while (iter != m_tags.end())
        {
            iter->second->Render((Identation){identation.Ident, identation.IdentNumber, identation.Level + 1});
            iter++;
        }

        RenderIdentation(m_ostream, identation);
        (*m_ostream) << L"</head>";
    }

    void HtmlHead::Dispose()
    {
        if (!m_Disposed)
        {
            m_Disposed = true;

            delete this;
        }
    }
} // namespace htmlCplusplus
