#include "CameraMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr(void)
	: m_pCameraSubject(CCameraSubject::GetInstance())
{
}

CCameraMgr::~CCameraMgr(void)
{
}

void CCameraMgr::SetPersCamera(const wstring & wstrCameraKey)
{
	auto iter = m_CameraMap[CAMTYPE_PERSPECTIVE].find(wstrCameraKey);

	if (iter != m_CameraMap[CAMTYPE_PERSPECTIVE].end())
	{
		m_pMatPersView = iter->second->GetViewMatrix();
		m_pMatPersProj = iter->second->GetProjMatrix();
		m_pCameraSubject->SetData(CCameraSubject::CSMSG_MATPERSVIEW, m_pMatPersView);
		m_pCameraSubject->SetData(CCameraSubject::CSMSG_MATPERSPROJ, m_pMatPersProj);
	}
}

void CCameraMgr::SetOrthoCamera(const wstring & wstrCameraKey)
{
	auto iter = m_CameraMap[CAMTYPE_ORTHOGRAPH].find(wstrCameraKey);

	if (iter != m_CameraMap[CAMTYPE_ORTHOGRAPH].end())
	{
		// 이거 두갠 솔까말 필요 없는거... 근데 혹시 몰라 해둠
		m_pMatOrthoView = iter->second->GetViewMatrix();
		m_pMatOrthoProj = iter->second->GetProjMatrix();

		m_pCameraSubject->SetData(CCameraSubject::CSMSG_MATORTHOVIEW, m_pMatOrthoView);
		m_pCameraSubject->SetData(CCameraSubject::CSMSG_MATORTHOPROJ, m_pMatOrthoProj);
	}
}

HRESULT CCameraMgr::InitCameraMgr(void)
{
	return S_OK;
}

void CCameraMgr::AddCamera(CAMERA_TYPE eCameraType, const wstring & wstrCameraKey, CCamera * pCamera)
{
	if (nullptr == pCamera) return;

	auto iter = m_CameraMap[eCameraType].find(wstrCameraKey);

	if (iter == m_CameraMap[eCameraType].end())
	{
		m_CameraMap[eCameraType].insert(MAPCAMERA::value_type(wstrCameraKey, pCamera));
	}
}

void CCameraMgr::RemoveCamera(CAMERA_TYPE eCameraType, const wstring& wstrCameraKey)
{
	auto iter = m_CameraMap[eCameraType].find(wstrCameraKey);

	if (iter != m_CameraMap[eCameraType].end())
		m_CameraMap[eCameraType].erase(iter);
}

void CCameraMgr::ClearCamera(void)
{
	for (size_t i = 0; i < CAMTYPE_END; ++i)
		m_CameraMap[i].clear();
}

void CCameraMgr::Release(void)
{
	for (size_t i = 0; i < CAMTYPE_END; ++i)
		m_CameraMap[i].clear();
}
