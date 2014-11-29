#include "StdAfx.h"
#include "Multi_Choice_Exgex.h"
#include <regex>
CMulti_Choice_Exgex::CMulti_Choice_Exgex(void)
{
}


CMulti_Choice_Exgex::~CMulti_Choice_Exgex(void)
{
}
void CommonParse(CString source, CString regex,vector<wstring> &vl)
{
	vl.clear();

	 wregex strRegex(regex);
	 wsmatch results;

	  wstring strInput = source;

	  std::wstring::const_iterator it=strInput.begin();//取头  
	  std::wstring::const_iterator end=strInput.end();//取尾

	  
	   if (regex_search(strInput,results,strRegex))  
	   {    
		   while (regex_search(it,end,results,strRegex))  
		   {    
			   vl.push_back(results[1]);//这里就得到分组1    	
			   it=results[0].second; 
		   }
	   }
}
void stringToCString(wstring str,CString &cstr)
{
	 cstr.Format(L"%s",str.c_str());
	 cstr.Replace(L"\n",L"");
	 cstr.Replace(L"A.",L"");
	 cstr.Replace(L"B.",L"");
	 cstr.Replace(L"C.",L"");
	 cstr.Replace(L"D.",L"");

	 cstr.Replace(L"A．",L"");
	 cstr.Replace(L"B．",L"");
	 cstr.Replace(L"C．",L"");
	 cstr.Replace(L"D．",L"");
	 cstr=cstr.Trim();
}
void CMulti_Choice_Exgex::Parse(CString source)
{
	m_list.clear();

	 vector<wstring> result_title;
	 vector<wstring> result_itemA;
	 vector<wstring> result_itemB;
	 vector<wstring> result_itemC;
	 vector<wstring> result_itemD;
		CommonParse(source,
			    L"(\\d+[\\.\\．].*)",//Title  L"(\\d+.*\r\n)",  
								//A (?<=\n)A.*(?=\n)
								//B (\nB.*\r\n)
								//C (\nC.*\r\n)
								//D (\nB.*\r\n)
			    result_title);
		CommonParse(source,
			    L"(A[\\.\\．].*)",
			    result_itemA);
		CommonParse(source,
			    L"(B[\\.\\．].*)",
			    result_itemB);
		CommonParse(source,
			    L"(C[\\.\\．].*)",
			    result_itemC);
		CommonParse(source,
			    L"(D[\\.\\．].*)",
			    result_itemD);

   for(int i=0;i<result_title.size();++i)
   {
	 CString tempTitle ; 

	 CModelChoice* obj = new CModelChoice;
     stringToCString(result_title[i], obj->m_title);
	 stringToCString(result_itemA[i], obj->m_choices[0]);
	 stringToCString(result_itemB[i], obj->m_choices[1]);
	 stringToCString(result_itemC[i], obj->m_choices[2]);
	 stringToCString(result_itemD[i], obj->m_choices[3]);

	 m_list.push_back(obj);
	// Util::LOG(tempTitle);
   }

 
}