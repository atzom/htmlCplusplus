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

#ifndef _html_IPage
#define _html_IPage

#include <ostream>
#include <string>
#include <map>

#include "Tag.h"

namespace htmlCplusplus
{
    class IPage
    {
    public:
        virtual void HttpHeadersClear() = 0;
        virtual void HttpHeadersSend() = 0;
        virtual void HttpHeadersAdd(std::string name, std::string content) = 0;

        virtual void HeadSetTitle(std::wstring title) = 0;
        virtual void HeadAddStyle(std::wstring style) = 0;
        virtual void HeadAddScript(std::wstring script) = 0;
        virtual void HeadAddLink(std::map<std::string, std::wstring> attributes) = 0;

        virtual void BodyAdd(std::string name, std::string content, bool escapeChars) = 0;
        virtual void BodyAdd(Tag *tag) = 0;

        virtual void Render() = 0;
    };

} // namespace htmlCplusplus

#endif