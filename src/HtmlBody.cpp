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

#include <algorithm>

#include "HtmlBody.h"

namespace htmlCplusplus
{
    HtmlBody::HtmlBody()
    {
    }

    HtmlBody::~HtmlBody()
    {
        std::list<ITag *> tags(m_Tags);
        std::list<ITag *>::iterator iter = tags.begin();

        while (iter != tags.end())
        {
            (*iter)->Dispose();
            iter++;
        }

        m_Tags.clear();
    }

    void HtmlBody::RemoveChild(IChild *child, bool dispose)
    {
        ITag *tag = dynamic_cast<ITag *>(child);

        if (tag != NULL)
        {
            std::list<ITag *> range{tag};

            std::list<ITag *>::iterator iter = std::find_first_of(m_Tags.begin(), m_Tags.end(), range.begin(), range.end(), [](ITag *left, ITag *right) -> bool {
                uintptr_t leftAddr, rightAddr;

                leftAddr = reinterpret_cast<uintptr_t>(left);
                rightAddr = reinterpret_cast<uintptr_t>(right);

                return leftAddr == rightAddr;
            });

            if (iter != m_Tags.end())
            {
                child->RemoveParent();

                m_Tags.erase(iter);

                if (dispose)
                    tag->Dispose();
            }
        }
    }

    void HtmlBody::SetBeautifier(IHtmlBeautify *beautify)
    {
        m_Beautify = beautify;

        if (m_Tags.size() > 0)
        {
            for (std::list<ITag *>::iterator iter = m_Tags.begin(); iter != m_Tags.end(); iter++)
            {
                (*iter)->SetBeautifier(m_Beautify);
            }
        }
    }

    void HtmlBody::Add(ITag *tag)
    {
        if (tag != NULL)
        {
            tag->SetParent(static_cast<IParent *>(this));
            tag->SetBeautifier(m_Beautify);

            m_Tags.push_back(tag);
        }
    }

    void HtmlBody::Render(Identation identation)
    {
        std::list<ITag *>::const_iterator iter = m_Tags.begin();

        while (iter != m_Tags.end())
        {
            (*iter)->Render((Identation){identation.Ident, identation.IdentNumber, identation.Level + 1});
            iter++;
        }
    }

} // namespace htmlCplusplus
