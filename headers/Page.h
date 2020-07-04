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


#ifndef _html_Page
#define _html_Page

#include <ostream>
#include <string>

#include "IHtmlBeautify.h"
#include "IHttpHeader.h"

#include "IPage.h"
#include "IHtmlHead.h"
#include "HtmlBody.h"
#include "Tag.h"

using namespace std;

namespace htmlCplusplus
{
	class Page: public IPage
	{

		private:

            std::wostream *m_ostream;

            Identation m_Identation;

            bool m_autoRender;

			bool m_httpHeadersSent;
			http::IHttpHeader *m_httpHeaders;

            IHtmlHead *m_htmlHead;
            HtmlBody m_htmlBody;
            
            IHtmlBeautify *m_Beautify;

            void RenderStart();
            void RenderHtmlHeaders();
            void RenderBodyStart();
            void RenderBody();
            void RenderBodyEnd();
            void RenderEnd();


		public:

			Page(std::wostream &ostr, std::string contentType = "text/html;charset=iso-8859-1", bool autoRender = false, Identation identation = (Identation){ true, 4, 1});
            Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, bool autoRender = false, Identation identation = (Identation){ true, 4, 1});
            Page(std::wostream &ostr, IHtmlHead *htmlHead, bool autoRender = false, Identation identation = (Identation){ true, 4, 1});
            Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, IHtmlHead *htmlHead, bool autoRender = false, Identation identation = (Identation){ true, 4, 1});
            Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, IHtmlHead *htmlHead, IHtmlBeautify *beautify, bool autoRender = false, Identation identation = (Identation){ true, 4, 1});
			~Page();

            void HttpHeadersClear();
			void HttpHeadersSend();
			void HttpHeadersAdd(string name, string content);

            void HeadSetTitle(std::wstring title);
            void HeadAddStyle(std::wstring style);
            void HeadAddScript(std::wstring script);
            void HeadAddLink(std::map<std::string, std::wstring> attributes);

            void BodyAdd(string name, string content, bool escapeChars);
            void BodyAdd(Tag *tag);

            void Render();
	};
}

#endif
