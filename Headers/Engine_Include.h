#ifndef Engine_Include_h__
#define Engine_Include_h__

#include "d3d9.h"
#include "d3dx9.h"

#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <ctime>
#include <random>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#include "Engine_enum.h"
#include "Engine_macro.h"
#include "Engine_struct.h"
#include "Engine_function.h"
#include "Engine_functor.h"
#include "Engine_math.h"

#pragma warning(disable : 4251)

using namespace std;

#endif // Engine_Include_h__
