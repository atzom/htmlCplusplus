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

#ifndef _html_HtmlHeaders
#define _html_HtmlHeaders

#include <ostream>
#include <string>
#include <list>
#include <map>

#include "IHtmlBeautify.h"
#include "IHtmlHead.h"
#include "HtmlString.h"
#include "ITag.h"

namespace htmlCplusplus
{
    class HtmlHead : public IHtmlHead
    {
    private:
        std::wostream *m_ostream;

        IHtmlBeautify *m_Beautify = NULL;

        IParent *m_Parent = NULL;

        std::map<std::string, ITag *> m_tags;

        bool m_Disposed = false;

    protected:
        ~HtmlHead();

        void RenderIdentation(std::wostream *ostr, Identation identation);

    public:
        HtmlHead(std::wostream &stream);

        void Dispose();

        void SetParent(IParentChildRelation *relation);
        void RemoveParent();

        void SetStream(std::wostream &ostr);
        void SetBeautifier(IHtmlBeautify *beautify);

        void SetTitle(std::wstring title);
        void SetBase(std::map<std::string, std::wstring> attributes);

        void AddStyle(std::wstring style);
        void AddScript(std::wstring script);

        void AddLink(std::map<std::string, std::wstring> attributes);
        void AddMeta(std::map<std::string, std::wstring> attributes);

        void Render(Identation identation);
    };
} // namespace htmlCplusplus

#endif
