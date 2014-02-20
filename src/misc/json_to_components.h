#ifndef _CHAOS3D_JSON_TO_COMPONENTS_H
#define _CHAOS3D_JSON_TO_COMPONENTS_H

#include "io/io_converter.h"
#include "io/json_loader.h"

#include "com/sprite2d/camera2d.h"

template<>
struct io_converter<json_loader, sprite2d::camera2d> {
    bool operator() (json_loader const&, sprite2d::camera2d&) const;
};


#endif