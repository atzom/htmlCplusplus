#include "Page.h"
#include "Tag.h"
#include "HtmlBody.h"
#include "HttpHeader.h"
#include "HtmlHead.h"
#include "HtmlBeautify.h"

#include <map>
#include <locale>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    auto loc = std::locale("el_GR.utf8");

    std::setlocale(LC_ALL, "el_GR.utf8");
    std::locale::global(loc);
    std::wcout.imbue(loc);

    htmlCplusplus::HtmlBeautify *beautify = new htmlCplusplus::HtmlBeautify();
    htmlCplusplus::http::HttpHeader *httpHeader = new htmlCplusplus::http::HttpHeader(std::wcout);
    htmlCplusplus::HtmlHead *htmlHead = new htmlCplusplus::HtmlHead(std::wcout);
    htmlCplusplus::Page page(std::wcout, httpHeader, htmlHead, beautify, false);

    htmlCplusplus::IHtmlBody *body = new htmlCplusplus::HtmlBody();

    htmlHead->SetTitle(L"htmlCplusplus Utility for C++");
    htmlHead->AddStyle(L".error { color:#001122; }");
    htmlHead->AddScript(L"function callme() { document.getElementById(\"txtArea\").innerHTML = \"Created by Andreas Tzomakas\"; }");
    htmlHead->AddMeta({{"content-type", L"text/html; charset=utf-8"}, {"http-equiv", L"content-type"}});

    htmlCplusplus::ITag *h1 = new htmlCplusplus::Tag("h1", "htmlCplusplus Utility for C++", true);
    htmlCplusplus::ITag *p = new htmlCplusplus::Tag("p");
    htmlCplusplus::ITag *b = new htmlCplusplus::Tag("b");
    htmlCplusplus::ITag *span = new htmlCplusplus::Tag("span", L"Ελληνικό περιεχόμενο!", true);
    htmlCplusplus::ITag *textarea = new htmlCplusplus::Tag("textarea", L"Παρακαλώ πατήστε πάνω στο κουμπί.", false);
    htmlCplusplus::ITag *btn = new htmlCplusplus::Tag("button", "C++", true);

    span->SetContentNewLines(false, false);

    p->AddTag(span);

    b->AddAttribute("style", "color: red;", false);

    b->AddTag(new htmlCplusplus::Tag("i", "Hello ", true));
    b->AddTag("u", "world", true);
    b->AddTag("del", "written", true);
    b->AddTag("ins", "from ", true);

    btn->AddAttribute("onclick", "callme(); return false;", false);
    b->AddTag(btn);

    p->AddTag(b);

    textarea->AddAttribute("id", "txtArea", false);
    textarea->AddAttribute("cols", "100", false);
    textarea->AddAttribute("rows", "20", false);

    page.SetBody(body);
    page.BodyAdd(h1);
    page.BodyAdd(p);
    page.BodyAdd(textarea);
    
    page.Render();

    return 0;
}