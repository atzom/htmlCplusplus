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


#include <iostream>
#include <sstream>
#include <iomanip>

#include "HtmlString.h"

namespace htmlCplusplus
{

    HtmlString::HtmlString()
    {
    }

    std::string HtmlString::RemoveInvalid(const std::string content)
    {
        std::string newContent = "";

        for (std::string::const_iterator iter = content.begin(); iter != content.end(); iter++)
        {
            switch (*iter)
            {
                case '<':
                case '>':
                case '&':
                case '"':
                    continue;

                default:
                    newContent.push_back(*iter);
            }
        }

        return newContent;
    }

    std::wstring HtmlString::RemoveInvalid(const std::wstring content)
    {
        std::wstring newContent = L"";

        for (std::wstring::const_iterator iter = content.begin(); iter != content.end(); iter++)
        {
            switch (*iter)
            {
                case '<':
                case '>':
                case '&':
                case '"':
                    continue;

                default:
                    newContent.push_back(*iter);
            }
        }

        return newContent;
    }


    std::string HtmlString::Escape(const std::string content)
    {
        std::string newContent = "";

        for (std::string::const_iterator iter = content.begin(); iter != content.end(); iter++)
        {
            switch (*iter)
            {
                case '<':
                    newContent.append("&lt;");
                    break;

                case '>':
                    newContent.append("&gt;");
                    break;

                case '&':
                    newContent.append("&amp;");
                    break;

                case '"':
                    newContent.append("&quot;");
                    break;

                default:
                    newContent.push_back(*iter);
            }
        }

        return newContent;

    }

    std::wstring HtmlString::Escape(const std::wstring content)
    {
        std::wstring newContent = L"";

        for (std::wstring::const_iterator iter = content.begin(); iter != content.end(); iter++)
        {
            switch (*iter)
            {
                case '<':
                    newContent.append(L"&lt;");
                    break;

                case '>':
                    newContent.append(L"&gt;");
                    break;

                case '&':
                    newContent.append(L"&amp;");
                    break;

                case '"':
                    newContent.append(L"&quot;");
                    break;

                default:
                    newContent.push_back(*iter);
            }
        }

        return newContent;

    }

    std::wstring HtmlString::ToWString(std::string content)
    {
        std::wstring wcontent;

        wcontent.assign(content.begin(), content.end());

        return wcontent;
    }

    std::string HtmlString::UrlEncode(std::string url)
    {
        std::stringstream encoded;

        for(std::string::const_iterator iter = url.begin(); iter != url.end(); iter++)
        {
            if 
            (
                (std::isdigit(*iter)) || 
                (std::isalpha(*iter)) || 
                (
                    (*iter == '-') || (*iter == '_') || (*iter == '.') || (*iter == '~')
                )
            )
            {
                encoded  << (*iter);
            }
            else
            {
                if (*iter == ' ')
                    encoded << '+';
                else if ((unsigned int)(*iter) < 16)
                    encoded << "%0" << std::setw(2) << std::hex << std::uppercase << ((unsigned int) (*iter));
                else
                    encoded << '%' << std::setw(2) << std::hex << std::uppercase << ((unsigned int) (*iter));
            }
        }

        return encoded.str();
    }

    std::string HtmlString::UrlDecode(std::string url)
    {
        std::stringstream decoded;

        std::string::const_iterator iter = url.begin();

        while (iter != url.end())
        {
            if 
            (
                (std::isdigit(*iter)) || 
                (std::isalpha(*iter)) || 
                (
                    (*iter == '-') || (*iter == '_') || (*iter == '.') || (*iter == '~')
                )
            )
            {
                decoded  << (*iter);
            }
            else
            {
                if (*iter == '+')
                    decoded << ' ';
                else if (*iter == '%')
                {
                    int chr;
                    std::stringstream hex;

                    hex << "0x";

                    iter++;

                    if (iter == url.end())
                        throw std::string("Invalid URL Encoding");

                    hex << (*iter);

                    iter++;

                    if (iter == url.end())
                        throw std::string("Invalid URL Encoding");

                    hex << (*iter);

                    hex.flags(std::ios::hex);
                    hex >> chr;

                    decoded << (char)chr;
                }
            }

            iter++;
        };

        return decoded.str();
    }
}
