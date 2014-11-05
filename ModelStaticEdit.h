#pragma once

typedef enum TAG
{
	TAG_QUESTION,
	TAG_ANSWER
}TAG;

typedef enum TYPE
{
	TYPE_TEXT,
	TYPE_IMAGE
}TYPE;
class CModelStaticEdit
{
public:
	CModelStaticEdit(void);
	~CModelStaticEdit(void);
	CStatic* m_static;
	CEdit*   m_edit;
	TAG m_tag;
	TYPE m_type;	
};

