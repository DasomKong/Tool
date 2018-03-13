#ifndef CameraMgr_h__
#define CameraMgr_h__

#include "CameraSubject.h"
#include "Camera.h"

BEGIN(Engine)

class ENGINE_DLL CCameraMgr
{
public:
	DECLARE_SINGLETON(CCameraMgr)
private:
	CCameraMgr(void);
	~CCameraMgr(void);

public: // Setter
	void SetPersCamera(const wstring& wstrCameraKey);
	void SetOrthoCamera(const wstring& wstrCameraKey);

public:
	HRESULT InitCameraMgr(void);
	void AddCamera(CAMERA_TYPE eCameraType, const wstring& wstrCameraKey, CCamera* pCamera);
	void RemoveCamera(CAMERA_TYPE eCameraType, const wstring& wstrCameraKey);
	void ClearCamera(void);

private:
	void Release(void);

private:
	typedef map<wstring, CCamera*>	MAPCAMERA;
	MAPCAMERA						m_CameraMap[CAMTYPE_END];

	CCameraSubject*					m_pCameraSubject = nullptr;

	D3DXMATRIX* m_pMatPersView = nullptr;
	D3DXMATRIX* m_pMatPersProj = nullptr;
	D3DXMATRIX* m_pMatOrthoView = nullptr;
	D3DXMATRIX* m_pMatOrthoProj = nullptr;
};

END

#endif // CameraMgr_h__
