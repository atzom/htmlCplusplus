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

#include "Page.h"
#include "Tag.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "HtmlHead.h"
#include "HttpHeader.h"

using namespace std;

namespace htmlCplusplus
{
    Page::Page(std::wostream &ostr, std::string contentType, bool autoRender, Identation identation)
    {
        m_ostream = &ostr;

        m_autoRender = autoRender;

        m_Identation = identation;

        m_httpHeadersSent = false;

        if (contentType.length() > 0)
        {
            m_httpHeaders = new http::HttpHeader(ostr);
            m_httpHeaders->SetParent(this);
            m_httpHeaders->Add("Content-Type", contentType);
        }
        else
        {
            m_httpHeaders = NULL;
        }

        m_Beautify = new HtmlBeautify();
        m_Beautify->SetParent(this);

        m_htmlHead = new htmlCplusplus::HtmlHead(ostr);
        m_htmlHead->SetParent(this);
        m_htmlHead->SetBeautifier(m_Beautify);

        if (autoRender)
        {
            HttpHeadersSend();

            RenderStart();
            RenderHtmlHeaders();
            RenderBodyStart();
        }
    }

    Page::Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, bool autoRender, Identation identation)
    {
        m_ostream = &ostr;

        m_autoRender = autoRender;

        m_Identation = identation;

        m_httpHeadersSent = false;
        m_httpHeaders = httpHeaders;

        if (m_httpHeaders != NULL)
        {
            m_httpHeaders->SetParent(this);
            m_httpHeaders->SetStream(ostr);
        }

        m_Beautify = new HtmlBeautify();
        m_Beautify->SetParent(this);

        m_htmlHead = new htmlCplusplus::HtmlHead(ostr);
        m_htmlHead->SetParent(this);
        m_htmlHead->SetBeautifier(m_Beautify);

        if (autoRender)
        {
            HttpHeadersSend();

            RenderStart();
            RenderHtmlHeaders();
            RenderBodyStart();
        }
    }

    Page::Page(std::wostream &ostr, IHtmlHead *htmlHead, bool autoRender, Identation identation)
    {
        m_ostream = &ostr;

        m_autoRender = autoRender;

        m_Identation = identation;

        m_httpHeadersSent = false;
        m_httpHeaders = NULL;

        m_Beautify = new HtmlBeautify();
        m_Beautify->SetParent(this);

        m_htmlHead = htmlHead;

        if (m_htmlHead)
        {
            m_htmlHead->SetParent(this);
            m_htmlHead->SetStream(ostr);
            m_htmlHead->SetBeautifier(m_Beautify);
        }

        if (autoRender)
        {
            HttpHeadersSend();

            RenderStart();
            RenderHtmlHeaders();
            RenderBodyStart();
        }
    }

    Page::Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, IHtmlHead *htmlHead, bool autoRender, Identation identation)
    {
        m_ostream = &ostr;

        m_autoRender = autoRender;

        m_Identation = identation;

        m_httpHeadersSent = false;
        m_httpHeaders = httpHeaders;

        if (m_httpHeaders != NULL)
        {
            m_httpHeaders->SetParent(this);
            m_httpHeaders->SetStream(ostr);
        }

        m_Beautify = new HtmlBeautify();
        m_Beautify->SetParent(this);

        m_htmlHead = htmlHead;

        if (m_htmlHead)
        {
            m_htmlHead->SetParent(this);
            m_htmlHead->SetStream(ostr);
            m_htmlHead->SetBeautifier(m_Beautify);
        }

        if (autoRender)
        {
            HttpHeadersSend();

            RenderStart();
            RenderHtmlHeaders();
            RenderBodyStart();
        }
    }

    Page::Page(std::wostream &ostr, http::IHttpHeader *httpHeaders, IHtmlHead *htmlHead, IHtmlBeautify *beautify, bool autoRender, Identation identation)
    {
        m_ostream = &ostr;

        m_autoRender = autoRender;

        m_Identation = identation;

        m_httpHeadersSent = false;
        m_httpHeaders = httpHeaders;

        if (m_httpHeaders != NULL)
        {
            m_httpHeaders->SetParent(this);
            m_httpHeaders->SetStream(ostr);
        }


        m_Beautify = beautify;

        if (m_Beautify)
            m_Beautify->SetParent(this);


        m_htmlHead = htmlHead;

        if (m_htmlHead)
        {
            m_htmlHead->SetParent(this);
            m_htmlHead->SetStream(ostr);
            m_htmlHead->SetBeautifier(m_Beautify);
        }

        if (autoRender)
        {
            HttpHeadersSend();

            RenderStart();
            RenderHtmlHeaders();
            RenderBodyStart();
        }
    }

    Page::~Page()
    {
        if (m_autoRender)
        {
            RenderBodyEnd();
            RenderEnd();
        }

        if (m_httpHeaders)
        {
            m_httpHeaders->Dispose();
            m_httpHeaders = NULL;
        }

        if (m_htmlHead)
        {
            m_htmlHead->Dispose();
            m_htmlHead = NULL;
        }

        if (m_Beautify)
        {
            m_Beautify->Dispose();
            m_Beautify = NULL;
        }
    }

    void Page::RemoveChild(IParentChildRelation *relation, bool dispose)
    {
        //TODO
        if (
                ((dynamic_cast<http::IHttpHeader *>(static_cast<IChild *>(relation))) != NULL) &&
                (reinterpret_cast<uintptr_t>((static_cast<http::IHttpHeader *>(static_cast<IChild *>(relation)))) == reinterpret_cast<uintptr_t>(m_httpHeaders))
        )
        {
            if (dispose)
                m_httpHeaders->Dispose();

            m_httpHeaders = NULL;
        }
        else if (
                ((dynamic_cast<IHtmlHead *>(static_cast<IChild *>(relation))) != NULL) &&
                (reinterpret_cast<uintptr_t>((static_cast<IHtmlHead *>(static_cast<IChild *>(relation)))) == reinterpret_cast<uintptr_t>(m_htmlHead))
        )
        {
            if (dispose)
                m_htmlHead->Dispose();

            m_htmlHead = NULL;
        }
        else if (
                ((dynamic_cast<IHtmlBeautify *>(static_cast<IChild *>(relation))) != NULL) &&
                (reinterpret_cast<uintptr_t>((static_cast<IHtmlBeautify *>(static_cast<IChild *>(relation)))) == reinterpret_cast<uintptr_t>(m_Beautify))
        )
        {
            if (dispose)
                m_Beautify->Dispose();

            m_Beautify = NULL;
        }
    }

    #pragma region Private methods

    void Page::RenderStart()
    {
        (*m_ostream) << L"<html>";
    }

    void Page::RenderHtmlHeaders()
    {
        if (m_htmlHead)
            m_htmlHead->Render((Identation){m_Identation.Ident, m_Identation.IdentNumber, m_Identation.Level});
    }

    void Page::RenderBodyStart()
    {
        if (m_Beautify)
            m_Beautify->RenderIdentation(m_ostream, m_Identation);

        (*m_ostream) << L"<body>";
    }

    void Page::RenderBody()
    {
        m_htmlBody.SetBeautifier(m_Beautify);
        m_htmlBody.Render((Identation){m_Identation.Ident, m_Identation.IdentNumber, m_Identation.Level});
    }

    void Page::RenderBodyEnd()
    {
        if (m_Beautify)
            m_Beautify->RenderIdentation(m_ostream, m_Identation);

        (*m_ostream) << L"</body>" << std::endl;
    }

    void Page::RenderEnd()
    {
        (*m_ostream) << L"</html>" << std::endl;
    }

    void Page::Render()
    {
        HttpHeadersSend();

        RenderStart();
        RenderHtmlHeaders();
        RenderBodyStart();
        RenderBody();
        RenderBodyEnd();
        RenderEnd();
    }

    #pragma endregion
    
    #pragma region Http Headers

    void Page::HttpHeadersAdd(string name, string content)
    {
        if (m_httpHeaders)
            m_httpHeaders->Add(name, content);
    }

    void Page::HttpHeadersClear()
    {
        if (m_httpHeaders)
            m_httpHeaders->Clear();
    }

    void Page::HttpHeadersSend()
    {
        if ((!m_httpHeadersSent) && (m_httpHeaders))
        {
            m_httpHeaders->Send();

            m_httpHeadersSent = true;
        }
    }

    #pragma endregion

} // namespace htmlCplusplus
