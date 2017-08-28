#pragma once

class CSkinMananger
{
public:
	CSkinMananger(void);
	~CSkinMananger(void);

	void ClearMap(){m_mapSkin.RemoveAll();}
	BOOL SetSkin(int nSkinId);
	int InitSkinMenu(HMENU hMenu, const SStringT &strSkinPath,int nStartId);
	SStringT ExtractSkinInfo(SStringT strSkinPath);
protected:
	SMap<int,SStringT> m_mapSkin;	//map of ID->skin path
};