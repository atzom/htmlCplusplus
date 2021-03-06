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
#include "IParent.h"

using namespace std;

namespace htmlCplusplus
{
    void Page::AddToBody(ITag *tag)
    {
        if (m_htmlBody != NULL)
        {
            m_htmlBody->Add(tag);
        }
        else
        {
            tag->Dispose();
        }
    }

    void Page::SetBody(IHtmlBody *body)
    {
        m_htmlBody = body;
    }

    void Page::BodyAdd(string name, string content, bool escapeChars)
    {
        Tag *tag = new Tag(*m_ostream);

        tag->SetName(name);
        tag->SetContent(content, escapeChars);

        if (m_autoRender)
        {
            tag->Render((Identation){m_Identation.Ident, m_Identation.IdentNumber, m_Identation.Level});
            tag->Dispose();
        }
        else
            AddToBody(tag);
    }

    void Page::BodyAdd(ITag *tag)
    {
        if (tag != NULL)
        {
            tag->SetStream(*m_ostream);
            tag->SetBeautifier(m_Beautify);

            if (m_autoRender)
                tag->Render((Identation){m_Identation.Ident, m_Identation.IdentNumber, m_Identation.Level});
            else
                AddToBody(tag);
        }
    }

} // namespace htmlCplusplus
