#pragma once

#define fw_delete(p) delete (p); (p) = NULL;
#define fw_delarr(p) delete [] (p); (p) = NULL;