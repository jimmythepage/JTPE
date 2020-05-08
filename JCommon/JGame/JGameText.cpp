#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameText::JGameText()
{

}
JGameText::~JGameText()
{
	if (mText)
	{
		delete mText;
		mText = NULL;
	}
}
void JGameText::Init(const std::string name, std::string applink, json text)
{
	JGameElement::Init(name,applink);
	ReadGeneralProperties(text);
	mRelProperties.FontSize = text[JsonDefine::FontSize];
	if (!text[JsonDefine::TextAlign].is_null())
	{
		std::string type = text[JsonDefine::TextAlign];
		if (type == JsonDefine::TextAlignMiddle)
		{
			mRelProperties.TextAlign= ALIGN_MIDDLE;
		}
		else if (type == JsonDefine::TextAlignRight)
		{
			mRelProperties.TextAlign = ALIGN_RIGHT;
		}
		else if (type == JsonDefine::TextAlignLeft)
		{
			mRelProperties.TextAlign = ALIGN_LEFT;
		}
	}
	if (!text[JsonDefine::FontStyle].is_null())
	{
		std::string type = text[JsonDefine::FontStyle];
		if (type == JsonDefine::FontStyleNormal)
		{
			mRelProperties.FontStyle = STYLE_NORMAL;
		}
		else if(type == JsonDefine::FontStyleBold)
		{
			mRelProperties.FontStyle = STYLE_BOLD;
		}
		else if (type == JsonDefine::FontStyleItalic)
		{
			mRelProperties.FontStyle = STYLE_ITALIC;
		}
		else if (type == JsonDefine::FontStyleUnderline)
		{
			mRelProperties.FontStyle = STYLE_UNDERLINE;
		}
		else if (type == JsonDefine::FontStyleStrikethrough)
		{
			mRelProperties.FontStyle = STYLE_STRIKETHROUGH;
		}
	}
	CalcAbsProperties();
	mText = new J::RENDER::JText();
	mText->Init(text[JsonDefine::Font], name + " text", mAbsProperties);
	SetText(gJTextDB.GetTextEntry(text[JsonDefine::TextAppLink]));
}
void JGameText::SetText(std::string text)
{
	mText->SetText(text);
}
void JGameText::Clear()
{
	JGameElement::Clear();
	mText->Clear();
}
void JGameText::Update()
{
	JGameElement::Update();
	mText->SetProperties(mAbsProperties);
}
void JGameText::Activate()
{
	JGameElement::Activate();
	mText->Activate();
}
void JGameText::Deactivate()
{
	JGameElement::Deactivate();
	mText->Deactivate();
}