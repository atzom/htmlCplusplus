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

#ifndef _html_ITag
#define _html_ITag

#include <string>
#include <cstdint>
#include <set>
#include <map>
#include <list>

#include "IHtmlBeautify.h"
#include "IParent.h"
#include "IChild.h"

namespace htmlCplusplus
{
    class ITag : public IParent, public IChild
    {
    public:
        virtual void Dispose() = 0;

        virtual void SetParent(IParent *parent) = 0;
        virtual void RemoveParent() = 0;
        virtual void RemoveChild(IChild *child, bool dispose) = 0;

        virtual void SetStream(std::wostream &ostr) = 0;
        virtual void SetBeautifier(IHtmlBeautify *beautify) = 0;

        virtual void SetName(std::string name, bool closeTag = true) = 0;
        virtual std::string GetName() = 0;

        virtual void SetContent(std::string content, bool escapeChars) = 0;
        virtual void SetContent(std::wstring content, bool escapeChars) = 0;
        virtual void SetContentNewLines(bool prefixNewLine, bool suffixNewLine) = 0;

        virtual void AddAttribute(std::string name, std::string content, bool escapeChars) = 0;
        virtual void AddAttribute(std::string name, std::wstring content, bool escapeChars) = 0;
        virtual void ClearAttributes() = 0;

        virtual void AddTag(ITag *tag) = 0;
        virtual void AddTag(std::string name, std::string content, bool escapeChars, bool closeTag = true) = 0;
        virtual void AddTag(std::string name, std::wstring content, bool escapeChars, bool closeTag = true) = 0;
        virtual void RemoveTag(ITag *tag) = 0;

        virtual void Render(Identation identation) = 0;
    };

} // namespace htmlCplusplus

#endif
