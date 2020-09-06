#include "Page.h"
#include "Tag.h"
#include "HtmlBody.h"

using namespace std;

int main(int argc, char **argv)
{
    htmlCplusplus::Page *page = new htmlCplusplus::Page(std::wcout);

    htmlCplusplus::IHtmlBody *body = new htmlCplusplus::HtmlBody();

    htmlCplusplus::ITag *h1 = new htmlCplusplus::Tag("h1", "htmlCplusplus Utility for C++", true);
    htmlCplusplus::ITag *p = new htmlCplusplus::Tag("p");
    htmlCplusplus::ITag *b = new htmlCplusplus::Tag("b");
    htmlCplusplus::ITag *span = new htmlCplusplus::Tag("span", "I am a text content into span!", true);
    htmlCplusplus::ITag *textarea = new htmlCplusplus::Tag("textarea", "click on the button!", false);
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

    page->HeadSetTitle(L"htmlCplusplus Utility for C++");
    page->HeadAddStyle(L".error { color: #001122; }");
    page->HeadAddScript(L"function callme() { document.getElementById(\"txtArea\").innerHTML = \"Created by Andreas Tzomakas\"; }");

    page->SetBody(body);
    page->BodyAdd(h1);
    page->BodyAdd(p);
    page->BodyAdd(textarea);
    
    page->Render();

    delete page;

    return 0;
}