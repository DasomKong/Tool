Engine::CManagement*		Get_Management(void)
{
	return Engine::CManagement::GetInstance();
}

Engine::CCameraSubject* Get_CameraSubject(void)
{
	return Engine::CCameraSubject::GetInstance();
}

Engine::CCameraMgr* Get_CameraMgr(void) 
{
	return Engine::CCameraMgr::GetInstance();
}