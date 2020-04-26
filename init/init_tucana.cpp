/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.
   Copyright (C) 2016 The CyanogenMod Project.
   Copyright (C) 2019-2020 The LineageOS Project.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[],
    char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void load_tucanaglobal() {
    property_override("ro.product.model", "Mi Note 10");
    property_override("ro.build.product", "tucana");
    property_override("ro.product.device", "tucana");
    property_override("ro.build.description", "tucana-user 10 QKQ1.190825.002 20.2.10 release-keys");
    property_override("ro.control_privapp_permissions", "log");
}

void vendor_load_properties() {
    std::string region = android::base::GetProperty("ro.boot.hwc", "");

    if (region.find("CN") != std::string::npos) {
        load_tucanaglobal();
    } else if (region.find("INDIA") != std::string::npos) {
        load_tucanaglobal();
    } else if (region.find("GLOBAL") != std::string::npos) {
        load_tucanaglobal();
    } else {
        LOG(ERROR) << __func__ << ": unexcepted region!";
    }

    property_override("ro.bluetooth.a2dp_offload.supported", "false");
    property_override("persist.bluetooth.a2dp_offload.disabled", "true");
    property_override("persist.bluetooth.bluetooth_audio_hal.disabled", "true");
    property_override("ro.oem_unlock_supported", "0");
    property_override("persist.vendor.sys.fp.fod.size.width_height", "445,1931");
    property_override("persist.vendor.qcom.bluetooth.enable.splita2dp", "false");
    property_override("vendor.audio.feature.a2dp_offload.enable", "false");
    property_override("ro.vendor.build.fingerprint", "google/coral/coral:10/QQ2A.200405.005/6254899:user/release-keys");
    property_override("ro.build.fingerprint", "google/coral/coral:10/QQ2A.200405.005/6254899:user/release-keys");
}
