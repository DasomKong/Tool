#ifndef CameraSubject_h__
#define CameraSubject_h__

#include "Subject.h"

BEGIN(Engine)

class ENGINE_DLL CCameraSubject : public CSubject
{
public:
	DECLARE_SINGLETON(CCameraSubject)
public:
	enum CAMERASUBJECT_MSG { CSMSG_MATPERSVIEW, CSMSG_MATPERSPROJ, CSMSG_MATORTHOVIEW, CSMSG_MATORTHOPROJ, CSMSG_END };

private:
	CCameraSubject(void);
	virtual ~CCameraSubject(void) override;

public: // Getter
	void* GetData(int iMessage);

public: // Setter
	void SetData(int iMessage, void* pData);
	void RemoveData(int iMessage, void* pData);

private:
	void Release(void);

private:
	void*		m_DataAry[CSMSG_END];
};

END

#endif // CameraSubject_h__
