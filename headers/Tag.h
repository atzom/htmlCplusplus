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

#ifndef _html_Tag
#define _html_Tag

#include <iostream>
#include <ostream>

#include <cstdlib>

#include <string>
#include <cstdint>
#include <set>
#include <map>
#include <list>

#include "HtmlBeautify.h"
#include "HtmlString.h"

namespace htmlCplusplus
{
    class Tag
    {
        friend class Page;
        friend class HtmlHead;
        friend class HtmlBody;

    private:
#ifdef TRACE_POINTERS
        static std::set<uintptr_t> *s_htmlTags;
#endif
        bool m_Disposed = false;

        std::wostream *m_ostream;

        IHtmlBeautify *m_Beautify = NULL;

        HtmlString m_htmlStr;

        Tag *m_Parent = NULL;

        std::list<Tag *> m_otherTags;
        std::map<std::string, std::wstring> m_properties;

        std::string m_name;
        std::wstring m_content;

        bool m_ContentPrefixNewLine = false;
        bool m_ContentSuffixNewLine = false;

        bool m_closeTag = true;

    protected:
        ~Tag();

        void SetParent(Tag *tag);
        void RemoveParent();

        void AddChild(Tag *tag);
        void RemoveChild(Tag *tag);

        void Dispose();
        

    public:
        Tag();
        Tag(std::wostream &ostr);
        Tag(std::string name, bool closeTag = true);
        Tag(std::string name, std::string content, bool escapeChars, bool closeTag = true);
        Tag(std::string name, std::wstring content, bool escapeChars, bool closeTag = true);

        void SetStream(std::wostream &ostr);
        void SetBeautifier(IHtmlBeautify *beautify);

        void SetName(std::string name, bool closeTag = true);
        std::string GetName() { return m_name; }

        void SetContent(std::string content, bool escapeChars);
        void SetContent(std::wstring content, bool escapeChars);
        void SetContentNewLines(bool prefixNewLine, bool suffixNewLine);

        void AddAttribute(std::string name, std::string content, bool escapeChars);
        void AddAttribute(std::string name, std::wstring content, bool escapeChars);
        void ClearAttributes();

        void AddTag(Tag *tag);
        void AddTag(std::string name, std::string content, bool escapeChars, bool closeTag = true);
        void AddTag(std::string name, std::wstring content, bool escapeChars, bool closeTag = true);
        void RemoveTag(Tag *tag);

        void Render(Identation identation);

#ifdef TRACE_POINTERS

        void *operator new(size_t size);
        void *operator new(size_t size, std::wostream &ostr);
        void *operator new[](size_t size, std::wostream &ostr);

        void operator delete(void *p);
        void operator delete[](void *p);

        static std::size_t TagsCount();
#endif
    };
} // namespace htmlCplusplus

#endif
