#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"
#include "CameraSubject.h"
#include "CameraMgr.h"

#include "Transform.h"

BEGIN(Engine)

inline CManagement* Get_Management(void);

inline CCameraSubject* Get_CameraSubject(void);

inline CCameraMgr* Get_CameraMgr(void);

#include "Export_Utility.inl"

END

#endif // Export_Utility_h__
