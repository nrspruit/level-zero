/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        auto pfnInit = context.zeDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeInitEpilogue( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnInit( flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeInitEpilogue( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader shall update the value with the
                                                        ///< total number of drivers available.
                                                        ///< if count is greater than the number of drivers available, then the
                                                        ///< loader shall update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles.
                                                        ///< if count is less than the number of drivers available, then the loader
                                                        ///< shall only retrieve that number of drivers.
        )
    {
        auto pfnGet = context.zeDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetEpilogue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGet( pCount, phDrivers );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetEpilogue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDrivers) && (i < *pCount); ++i){
                if (phDrivers[i]){
                    context.handleLifetime->addHandle( phDrivers[i] );
                    context.handleLifetime->addDependent( pCount, phDrivers[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;

        if( nullptr == pfnGetApiVersion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetApiVersionPrologue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetApiVersionPrologue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetApiVersionEpilogue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetApiVersion( hDriver, version );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetApiVersionEpilogue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Driver.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetPropertiesPrologue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetPropertiesPrologue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetPropertiesEpilogue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetProperties( hDriver, pDriverProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetPropertiesEpilogue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    {
        auto pfnGetIpcProperties = context.zeDdiTable.Driver.pfnGetIpcProperties;

        if( nullptr == pfnGetIpcProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetIpcPropertiesPrologue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetIpcPropertiesPrologue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetIpcPropertiesEpilogue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIpcProperties( hDriver, pIpcProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetIpcPropertiesEpilogue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of extension properties available.
                                                        ///< if count is greater than the number of extension properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< extension properties available.
        ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties.
                                                        ///< if count is less than the number of extension properties available,
                                                        ///< then driver shall only retrieve that number of extension properties.
        )
    {
        auto pfnGetExtensionProperties = context.zeDdiTable.Driver.pfnGetExtensionProperties;

        if( nullptr == pfnGetExtensionProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionPropertiesEpilogue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetExtensionPropertiesEpilogue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionFunctionAddressEpilogue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetExtensionFunctionAddressEpilogue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetLastErrorDescription(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        auto pfnGetLastErrorDescription = context.zeDdiTable.Driver.pfnGetLastErrorDescription;

        if( nullptr == pfnGetLastErrorDescription )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetLastErrorDescriptionPrologue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetLastErrorDescriptionPrologue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetLastErrorDescriptionEpilogue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetLastErrorDescription( hDriver, ppString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverGetLastErrorDescriptionEpilogue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of devices available.
                                                        ///< if count is greater than the number of devices available, then the
                                                        ///< driver shall update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices.
                                                        ///< if count is less than the number of devices available, then driver
                                                        ///< shall only retrieve that number of devices.
        )
    {
        auto pfnGet = context.zeDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetEpilogue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGet( hDriver, pCount, phDevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetEpilogue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDevices) && (i < *pCount); ++i){
                if (phDevices[i]){
                    context.handleLifetime->addHandle( phDevices[i] );
                    context.handleLifetime->addDependent( hDriver, phDevices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetRootDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    {
        auto pfnGetRootDevice = context.zeDdiTable.Device.pfnGetRootDevice;

        if( nullptr == pfnGetRootDevice )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetRootDevicePrologue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetRootDevicePrologue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetRootDeviceEpilogue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetRootDevice( hDevice, phRootDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetRootDeviceEpilogue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-devices available.
                                                        ///< if count is greater than the number of sub-devices available, then the
                                                        ///< driver shall update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices.
                                                        ///< if count is less than the number of sub-devices available, then driver
                                                        ///< shall only retrieve that number of sub-devices.
        )
    {
        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;

        if( nullptr == pfnGetSubDevices )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetSubDevicesPrologue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetSubDevicesPrologue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetSubDevicesEpilogue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetSubDevicesEpilogue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubdevices) && (i < *pCount); ++i){
                if (phSubdevices[i]){
                    context.handleLifetime->addHandle( phSubdevices[i] );
                    context.handleLifetime->addDependent( hDevice, phSubdevices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetPropertiesPrologue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetPropertiesPrologue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetPropertiesEpilogue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetProperties( hDevice, pDeviceProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetPropertiesEpilogue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;

        if( nullptr == pfnGetComputeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetComputePropertiesPrologue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetComputePropertiesPrologue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetComputePropertiesEpilogue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetComputeProperties( hDevice, pComputeProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetComputePropertiesEpilogue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetModuleProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    {
        auto pfnGetModuleProperties = context.zeDdiTable.Device.pfnGetModuleProperties;

        if( nullptr == pfnGetModuleProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetModulePropertiesPrologue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetModulePropertiesPrologue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetModulePropertiesEpilogue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetModuleProperties( hDevice, pModuleProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetModulePropertiesEpilogue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCommandQueueGroupProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCommandQueueGroupProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of command queue group properties available.
                                                        ///< if count is greater than the number of command queue group properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of command queue group properties available.
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties.
                                                        ///< if count is less than the number of command queue group properties
                                                        ///< available, then driver shall only retrieve that number of command
                                                        ///< queue group properties.
        )
    {
        auto pfnGetCommandQueueGroupProperties = context.zeDdiTable.Device.pfnGetCommandQueueGroupProperties;

        if( nullptr == pfnGetCommandQueueGroupProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetCommandQueueGroupPropertiesPrologue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetCommandQueueGroupPropertiesPrologue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCommandQueueGroupPropertiesEpilogue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetCommandQueueGroupPropertiesEpilogue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of memory properties available.
                                                        ///< if count is greater than the number of memory properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties.
                                                        ///< if count is less than the number of memory properties available, then
                                                        ///< driver shall only retrieve that number of memory properties.
        )
    {
        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;

        if( nullptr == pfnGetMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetMemoryPropertiesPrologue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetMemoryPropertiesPrologue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryPropertiesEpilogue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetMemoryPropertiesEpilogue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;

        if( nullptr == pfnGetMemoryAccessProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetMemoryAccessPropertiesPrologue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetMemoryAccessPropertiesPrologue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryAccessPropertiesEpilogue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetMemoryAccessPropertiesEpilogue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of cache properties available.
                                                        ///< if count is greater than the number of cache properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< cache properties available.
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache properties.
                                                        ///< if count is less than the number of cache properties available, then
                                                        ///< driver shall only retrieve that number of cache properties.
        )
    {
        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;

        if( nullptr == pfnGetCacheProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetCachePropertiesPrologue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetCachePropertiesPrologue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCachePropertiesEpilogue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetCacheProperties( hDevice, pCount, pCacheProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetCachePropertiesEpilogue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;

        if( nullptr == pfnGetImageProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetImagePropertiesPrologue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetImagePropertiesPrologue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetImagePropertiesEpilogue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetImageProperties( hDevice, pImageProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetImagePropertiesEpilogue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetExternalMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    {
        auto pfnGetExternalMemoryProperties = context.zeDdiTable.Device.pfnGetExternalMemoryProperties;

        if( nullptr == pfnGetExternalMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetExternalMemoryPropertiesPrologue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetExternalMemoryPropertiesPrologue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetExternalMemoryPropertiesEpilogue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetExternalMemoryPropertiesEpilogue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetP2PProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;

        if( nullptr == pfnGetP2PProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetP2PPropertiesPrologue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetP2PPropertiesPrologue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetP2PPropertiesEpilogue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetP2PPropertiesEpilogue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceCanAccessPeer
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;

        if( nullptr == pfnCanAccessPeer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceCanAccessPeerPrologue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceCanAccessPeerPrologue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceCanAccessPeerEpilogue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCanAccessPeer( hDevice, hPeerDevice, value );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceCanAccessPeerEpilogue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnGetStatus = context.zeDdiTable.Device.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetStatusPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetStatusPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetStatusEpilogue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetStatus( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetStatusEpilogue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetGlobalTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value
        )
    {
        auto pfnGetGlobalTimestamps = context.zeDdiTable.Device.pfnGetGlobalTimestamps;

        if( nullptr == pfnGetGlobalTimestamps )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetGlobalTimestampsPrologue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetGlobalTimestampsPrologue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetGlobalTimestampsEpilogue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetGlobalTimestampsEpilogue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        auto pfnCreate = context.zeDdiTable.Context.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextCreatePrologue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextCreatePrologue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreateEpilogue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hDriver, desc, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextCreateEpilogue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreateEx
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreateEx(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< context has visibility.
                                                        ///< if nullptr, then all devices and any sub-devices supported by the
                                                        ///< driver instance are
                                                        ///< visible to the context.
                                                        ///< otherwise, the context only has visibility to the devices and any
                                                        ///< sub-devices of the
                                                        ///< devices in this array.
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        auto pfnCreateEx = context.zeDdiTable.Context.pfnCreateEx;

        if( nullptr == pfnCreateEx )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextCreateExPrologue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextCreateExPrologue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreateExEpilogue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextCreateExEpilogue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Context.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextDestroyPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextDestroyPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextDestroyEpilogue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextDestroyEpilogue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    {
        auto pfnGetStatus = context.zeDdiTable.Context.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextGetStatusPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextGetStatusPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextGetStatusEpilogue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetStatus( hContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextGetStatusEpilogue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueCreatePrologue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueCreatePrologue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueCreateEpilogue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phCommandQueue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueCreateEpilogue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandQueue){
                context.handleLifetime->addHandle( *phCommandQueue );
                context.handleLifetime->addDependent( hContext, *phCommandQueue );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueDestroyPrologue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueDestroyPrologue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueDestroyEpilogue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hCommandQueue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueDestroyEpilogue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;

        if( nullptr == pfnExecuteCommandLists )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueExecuteCommandListsPrologue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueExecuteCommandListsPrologue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueExecuteCommandListsEpilogue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueExecuteCommandListsEpilogue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the command queue;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;

        if( nullptr == pfnSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueSynchronizePrologue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueSynchronizePrologue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueSynchronizeEpilogue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSynchronize( hCommandQueue, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueSynchronizeEpilogue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetOrdinal(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal
        )
    {
        auto pfnGetOrdinal = context.zeDdiTable.CommandQueue.pfnGetOrdinal;

        if( nullptr == pfnGetOrdinal )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueGetOrdinalPrologue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueGetOrdinalPrologue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueGetOrdinalEpilogue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetOrdinal( hCommandQueue, pOrdinal );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueGetOrdinalEpilogue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetIndex(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pIndex                                ///< [out] command queue index within the group
        )
    {
        auto pfnGetIndex = context.zeDdiTable.CommandQueue.pfnGetIndex;

        if( nullptr == pfnGetIndex )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueGetIndexPrologue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueGetIndexPrologue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueGetIndexEpilogue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIndex( hCommandQueue, pIndex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandQueueGetIndexEpilogue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreatePrologue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListCreatePrologue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateEpilogue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreateEpilogue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList );
                context.handleLifetime->addDependent( hContext, *phCommandList );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateImmediate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;

        if( nullptr == pfnCreateImmediate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreateImmediatePrologue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListCreateImmediatePrologue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateImmediateEpilogue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreateImmediateEpilogue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList , false);
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListDestroyPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListDestroyPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListDestroyEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListDestroyEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListClosePrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListClosePrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCloseEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnClose( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCloseEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListResetPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListResetPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListResetEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnReset( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListResetEpilogue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWriteGlobalTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWriteGlobalTimestamp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                        ///< be 8byte-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        )
    {
        auto pfnAppendWriteGlobalTimestamp = context.zeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp;

        if( nullptr == pfnAppendWriteGlobalTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendWriteGlobalTimestampPrologue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendWriteGlobalTimestampPrologue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWriteGlobalTimestampEpilogue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendWriteGlobalTimestampEpilogue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListHostSynchronize(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the immediate command list
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the immediate command list;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto pfnHostSynchronize = context.zeDdiTable.CommandList.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListHostSynchronizePrologue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListHostSynchronizePrologue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListHostSynchronizeEpilogue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnHostSynchronize( hCommandList, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListHostSynchronizeEpilogue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetDeviceHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetDeviceHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
        )
    {
        auto pfnGetDeviceHandle = context.zeDdiTable.CommandList.pfnGetDeviceHandle;

        if( nullptr == pfnGetDeviceHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetDeviceHandlePrologue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListGetDeviceHandlePrologue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetDeviceHandleEpilogue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetDeviceHandle( hCommandList, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetDeviceHandleEpilogue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetContextHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
        )
    {
        auto pfnGetContextHandle = context.zeDdiTable.CommandList.pfnGetContextHandle;

        if( nullptr == pfnGetContextHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetContextHandlePrologue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListGetContextHandlePrologue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetContextHandleEpilogue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetContextHandle( hCommandList, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetContextHandleEpilogue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetOrdinal(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
        )
    {
        auto pfnGetOrdinal = context.zeDdiTable.CommandList.pfnGetOrdinal;

        if( nullptr == pfnGetOrdinal )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetOrdinalPrologue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListGetOrdinalPrologue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetOrdinalEpilogue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetOrdinal( hCommandList, pOrdinal );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetOrdinalEpilogue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateGetIndex(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                        ///< command list is submitted
        )
    {
        auto pfnImmediateGetIndex = context.zeDdiTable.CommandList.pfnImmediateGetIndex;

        if( nullptr == pfnImmediateGetIndex )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListImmediateGetIndexPrologue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListImmediateGetIndexPrologue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListImmediateGetIndexEpilogue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnImmediateGetIndex( hCommandListImmediate, pIndex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListImmediateGetIndexEpilogue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListIsImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListIsImmediate(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                        ///< command list (true) or not (false)
        )
    {
        auto pfnIsImmediate = context.zeDdiTable.CommandList.pfnIsImmediate;

        if( nullptr == pfnIsImmediate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListIsImmediatePrologue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListIsImmediatePrologue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListIsImmediateEpilogue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnIsImmediate( hCommandList, pIsImmediate );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListIsImmediateEpilogue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;

        if( nullptr == pfnAppendBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendBarrierPrologue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendBarrierPrologue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendBarrierEpilogue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendBarrierEpilogue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

        if( nullptr == pfnAppendMemoryRangesBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryRangesBarrierPrologue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryRangesBarrierPrologue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryRangesBarrierEpilogue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryRangesBarrierEpilogue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextSystemBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnSystemBarrier = context.zeDdiTable.Context.pfnSystemBarrier;

        if( nullptr == pfnSystemBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextSystemBarrierPrologue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextSystemBarrierPrologue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextSystemBarrierEpilogue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSystemBarrier( hContext, hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextSystemBarrierEpilogue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;

        if( nullptr == pfnAppendMemoryCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopyPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyEpilogue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyEpilogue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;

        if( nullptr == pfnAppendMemoryFill )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryFillPrologue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryFillPrologue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryFillEpilogue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryFillEpilogue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

        if( nullptr == pfnAppendMemoryCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyRegionPrologue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopyRegionPrologue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyRegionEpilogue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyRegionEpilogue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyFromContext
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyFromContext(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_context_handle_t hContextSrc,                ///< [in] handle of source context object
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendMemoryCopyFromContext = context.zeDdiTable.CommandList.pfnAppendMemoryCopyFromContext;

        if( nullptr == pfnAppendMemoryCopyFromContext )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyFromContextPrologue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopyFromContextPrologue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyFromContextEpilogue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryCopyFromContextEpilogue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;

        if( nullptr == pfnAppendImageCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyPrologue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyPrologue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyEpilogue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyEpilogue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;

        if( nullptr == pfnAppendImageCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyRegionPrologue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyRegionPrologue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyRegionEpilogue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyRegionEpilogue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;

        if( nullptr == pfnAppendImageCopyToMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyToMemoryPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyToMemoryPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemoryEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyToMemoryEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

        if( nullptr == pfnAppendImageCopyFromMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyFromMemoryPrologue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyFromMemoryPrologue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemoryEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyFromMemoryEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;

        if( nullptr == pfnAppendMemoryPrefetch )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryPrefetchPrologue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryPrefetchPrologue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryPrefetchEpilogue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemoryPrefetchEpilogue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;

        if( nullptr == pfnAppendMemAdvise )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemAdvisePrologue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemAdvisePrologue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemAdviseEpilogue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendMemAdviseEpilogue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolCreatePrologue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolCreatePrologue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCreateEpilogue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolCreateEpilogue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEventPool){
                context.handleLifetime->addHandle( *phEventPool );
                context.handleLifetime->addDependent( hContext, *phEventPool );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolDestroyPrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolDestroyPrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolDestroyEpilogue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolDestroyEpilogue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventCreatePrologue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventCreatePrologue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventCreateEpilogue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hEventPool, desc, phEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventCreateEpilogue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEvent){
                context.handleLifetime->addHandle( *phEvent );
                context.handleLifetime->addDependent( hEventPool, *phEvent );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventDestroyPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventDestroyPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventDestroyEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventDestroyEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetIpcHandlePrologue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolGetIpcHandlePrologue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetIpcHandleEpilogue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIpcHandle( hEventPool, phIpc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetIpcHandleEpilogue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        )
    {
        auto pfnPutIpcHandle = context.zeDdiTable.EventPool.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolPutIpcHandlePrologue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolPutIpcHandlePrologue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolPutIpcHandleEpilogue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnPutIpcHandle( hContext, hIpc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolPutIpcHandleEpilogue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolOpenIpcHandlePrologue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolOpenIpcHandlePrologue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolOpenIpcHandleEpilogue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolOpenIpcHandleEpilogue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolCloseIpcHandlePrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolCloseIpcHandlePrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCloseIpcHandleEpilogue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCloseIpcHandle( hEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolCloseIpcHandleEpilogue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;

        if( nullptr == pfnAppendSignalEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendSignalEventPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendSignalEventPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendSignalEventEpilogue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendSignalEvent( hCommandList, hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendSignalEventEpilogue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitOnEvents
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    {
        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;

        if( nullptr == pfnAppendWaitOnEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendWaitOnEventsPrologue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendWaitOnEventsPrologue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWaitOnEventsEpilogue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendWaitOnEventsEpilogue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;

        if( nullptr == pfnHostSignal )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostSignalPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostSignalPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSignalEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnHostSignal( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostSignalEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostSynchronizePrologue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostSynchronizePrologue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSynchronizeEpilogue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnHostSynchronize( hEvent, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostSynchronizeEpilogue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryStatusPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryStatusPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryStatusEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryStatus( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryStatusEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;

        if( nullptr == pfnAppendEventReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendEventResetPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendEventResetPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendEventResetEpilogue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendEventReset( hCommandList, hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendEventResetEpilogue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostReset
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostReset = context.zeDdiTable.Event.pfnHostReset;

        if( nullptr == pfnHostReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostResetPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostResetPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostResetEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnHostReset( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventHostResetEpilogue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        auto pfnQueryKernelTimestamp = context.zeDdiTable.Event.pfnQueryKernelTimestamp;

        if( nullptr == pfnQueryKernelTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryKernelTimestampPrologue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryKernelTimestampPrologue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestampEpilogue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryKernelTimestamp( hEvent, dstptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryKernelTimestampEpilogue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendQueryKernelTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendQueryKernelTimestamps(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] the number of timestamp events to query
        ze_event_handle_t* phEvents,                    ///< [in][range(0, numEvents)] handles of timestamp events to query
        void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                        ///< be written; must be size-aligned.
        const size_t* pOffsets,                         ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                        ///< results; address must be 4byte-aligned and offsets must be
                                                        ///< size-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        )
    {
        auto pfnAppendQueryKernelTimestamps = context.zeDdiTable.CommandList.pfnAppendQueryKernelTimestamps;

        if( nullptr == pfnAppendQueryKernelTimestamps )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendQueryKernelTimestampsPrologue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendQueryKernelTimestampsPrologue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendQueryKernelTimestampsEpilogue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendQueryKernelTimestampsEpilogue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetEventPool
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetEventPool(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
        )
    {
        auto pfnGetEventPool = context.zeDdiTable.Event.pfnGetEventPool;

        if( nullptr == pfnGetEventPool )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetEventPoolPrologue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventGetEventPoolPrologue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetEventPoolEpilogue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetEventPool( hEvent, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetEventPoolEpilogue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetSignalScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetSignalScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                        ///< hierarchies that are flushed on a signal action before the event is
                                                        ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        auto pfnGetSignalScope = context.zeDdiTable.Event.pfnGetSignalScope;

        if( nullptr == pfnGetSignalScope )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetSignalScopePrologue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventGetSignalScopePrologue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetSignalScopeEpilogue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetSignalScope( hEvent, pSignalScope );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetSignalScopeEpilogue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetWaitScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetWaitScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                        ///< hierarchies invalidated on a wait action after the event is complete.
                                                        ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        auto pfnGetWaitScope = context.zeDdiTable.Event.pfnGetWaitScope;

        if( nullptr == pfnGetWaitScope )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetWaitScopePrologue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventGetWaitScopePrologue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetWaitScopeEpilogue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetWaitScope( hEvent, pWaitScope );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventGetWaitScopeEpilogue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetContextHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
        )
    {
        auto pfnGetContextHandle = context.zeDdiTable.EventPool.pfnGetContextHandle;

        if( nullptr == pfnGetContextHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetContextHandlePrologue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolGetContextHandlePrologue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetContextHandleEpilogue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetContextHandle( hEventPool, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetContextHandleEpilogue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetFlags
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetFlags(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                        ///< valid combination of ::ze_event_pool_flag_t
        )
    {
        auto pfnGetFlags = context.zeDdiTable.EventPool.pfnGetFlags;

        if( nullptr == pfnGetFlags )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetFlagsPrologue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolGetFlagsPrologue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetFlagsEpilogue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetFlags( hEventPool, pFlags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventPoolGetFlagsEpilogue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceCreatePrologue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceCreatePrologue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceCreateEpilogue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hCommandQueue, desc, phFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceCreateEpilogue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phFence){
                context.handleLifetime->addHandle( *phFence );
                context.handleLifetime->addDependent( hCommandQueue, *phFence );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceDestroyPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceDestroyPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceDestroyEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceDestroyEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceHostSynchronizePrologue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceHostSynchronizePrologue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceHostSynchronizeEpilogue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnHostSynchronize( hFence, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceHostSynchronizeEpilogue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceQueryStatusPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceQueryStatusPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceQueryStatusEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryStatus( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceQueryStatusEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnReset = context.zeDdiTable.Fence.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceResetPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceResetPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceResetEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnReset( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFenceResetEpilogue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetPropertiesPrologue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetPropertiesPrologue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetPropertiesEpilogue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetProperties( hDevice, desc, pImageProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetPropertiesEpilogue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeImageCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageCreatePrologue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageCreatePrologue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageCreateEpilogue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageCreateEpilogue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImage){
                context.handleLifetime->addHandle( *phImage );
                context.handleLifetime->addDependent( hContext, *phImage );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageDestroyPrologue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageDestroyPrologue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageDestroyEpilogue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageDestroyEpilogue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocShared
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocShared(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        auto pfnAllocShared = context.zeDdiTable.Mem.pfnAllocShared;

        if( nullptr == pfnAllocShared )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocSharedPrologue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocSharedPrologue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocSharedEpilogue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocSharedEpilogue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocDevice(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        auto pfnAllocDevice = context.zeDdiTable.Mem.pfnAllocDevice;

        if( nullptr == pfnAllocDevice )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocDevicePrologue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocDevicePrologue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocDeviceEpilogue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocDeviceEpilogue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocHost
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        auto pfnAllocHost = context.zeDdiTable.Mem.pfnAllocHost;

        if( nullptr == pfnAllocHost )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocHostPrologue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocHostPrologue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocHostEpilogue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAllocHost( hContext, host_desc, size, alignment, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemAllocHostEpilogue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto pfnFree = context.zeDdiTable.Mem.pfnFree;

        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemFreePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemFreePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFreeEpilogue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnFree( hContext, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemFreeEpilogue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAllocProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAllocProperties(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        auto pfnGetAllocProperties = context.zeDdiTable.Mem.pfnGetAllocProperties;

        if( nullptr == pfnGetAllocProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAllocPropertiesPrologue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAllocPropertiesPrologue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAllocPropertiesEpilogue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAllocPropertiesEpilogue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAddressRange
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAddressRange(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto pfnGetAddressRange = context.zeDdiTable.Mem.pfnGetAddressRange;

        if( nullptr == pfnGetAddressRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAddressRangePrologue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAddressRangePrologue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAddressRangeEpilogue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetAddressRange( hContext, ptr, pBase, pSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAddressRangeEpilogue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        auto pfnGetIpcHandle = context.zeDdiTable.Mem.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetIpcHandlePrologue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetIpcHandlePrologue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandleEpilogue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIpcHandle( hContext, ptr, pIpcHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetIpcHandleEpilogue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandleFromFileDescriptorExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandleFromFileDescriptorExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        auto pfnGetIpcHandleFromFileDescriptorExp = context.zeDdiTable.MemExp.pfnGetIpcHandleFromFileDescriptorExp;

        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetIpcHandleFromFileDescriptorExpPrologue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetIpcHandleFromFileDescriptorExpPrologue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandleFromFileDescriptorExpEpilogue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetIpcHandleFromFileDescriptorExpEpilogue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetFileDescriptorFromIpcHandleExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetFileDescriptorFromIpcHandleExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        )
    {
        auto pfnGetFileDescriptorFromIpcHandleExp = context.zeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp;

        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetFileDescriptorFromIpcHandleExpPrologue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetFileDescriptorFromIpcHandleExpPrologue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetFileDescriptorFromIpcHandleExpEpilogue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetFileDescriptorFromIpcHandleExpEpilogue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    {
        auto pfnPutIpcHandle = context.zeDdiTable.Mem.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemPutIpcHandlePrologue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemPutIpcHandlePrologue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemPutIpcHandleEpilogue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnPutIpcHandle( hContext, handle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemPutIpcHandleEpilogue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        auto pfnOpenIpcHandle = context.zeDdiTable.Mem.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemOpenIpcHandlePrologue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemOpenIpcHandlePrologue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemOpenIpcHandleEpilogue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemOpenIpcHandleEpilogue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto pfnCloseIpcHandle = context.zeDdiTable.Mem.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemCloseIpcHandlePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemCloseIpcHandlePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemCloseIpcHandleEpilogue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCloseIpcHandle( hContext, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemCloseIpcHandleEpilogue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemSetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemSetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        )
    {
        auto pfnSetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnSetAtomicAccessAttributeExp;

        if( nullptr == pfnSetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemSetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemSetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemSetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemSetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        )
    {
        auto pfnGetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnGetAtomicAccessAttributeExp;

        if( nullptr == pfnGetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleCreatePrologue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleCreatePrologue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleCreateEpilogue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleCreateEpilogue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phModule){
                context.handleLifetime->addHandle( *phModule );
                context.handleLifetime->addDependent( hContext, *phModule );

            }
            if (phBuildLog){
                context.handleLifetime->addHandle( *phBuildLog );
                context.handleLifetime->addDependent( hContext, *phBuildLog );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleDestroyPrologue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleDestroyPrologue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDestroyEpilogue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hModule );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleDestroyEpilogue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDynamicLink
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        )
    {
        auto pfnDynamicLink = context.zeDdiTable.Module.pfnDynamicLink;

        if( nullptr == pfnDynamicLink )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleDynamicLinkPrologue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleDynamicLinkPrologue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDynamicLinkEpilogue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDynamicLink( numModules, phModules, phLinkLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleDynamicLinkEpilogue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleBuildLogDestroyPrologue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleBuildLogDestroyPrologue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogDestroyEpilogue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hModuleBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleBuildLogDestroyEpilogue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogGetString
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;

        if( nullptr == pfnGetString )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleBuildLogGetStringPrologue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleBuildLogGetStringPrologue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogGetStringEpilogue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleBuildLogGetStringEpilogue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetNativeBinary
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;

        if( nullptr == pfnGetNativeBinary )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetNativeBinaryPrologue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetNativeBinaryPrologue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetNativeBinaryEpilogue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetNativeBinaryEpilogue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetGlobalPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    {
        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;

        if( nullptr == pfnGetGlobalPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetGlobalPointerPrologue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetGlobalPointerPrologue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetGlobalPointerEpilogue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetGlobalPointerEpilogue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetKernelNames(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of names available.
                                                        ///< if count is greater than the number of names available, then the
                                                        ///< driver shall update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions.
                                                        ///< if count is less than the number of names available, then driver shall
                                                        ///< only retrieve that number of names.
        )
    {
        auto pfnGetKernelNames = context.zeDdiTable.Module.pfnGetKernelNames;

        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetKernelNamesPrologue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetKernelNamesPrologue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetKernelNamesEpilogue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetKernelNames( hModule, pCount, pNames );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetKernelNamesEpilogue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Module.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetPropertiesPrologue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetPropertiesPrologue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetPropertiesEpilogue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetProperties( hModule, pModuleProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetPropertiesEpilogue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelCreatePrologue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelCreatePrologue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelCreateEpilogue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hModule, desc, phKernel );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelCreateEpilogue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phKernel){
                context.handleLifetime->addHandle( *phKernel );
                context.handleLifetime->addDependent( hModule, *phKernel );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelDestroyPrologue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelDestroyPrologue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelDestroyEpilogue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hKernel );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelDestroyEpilogue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;

        if( nullptr == pfnGetFunctionPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetFunctionPointerPrologue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetFunctionPointerPrologue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetFunctionPointerEpilogue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleGetFunctionPointerEpilogue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGroupSize
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;

        if( nullptr == pfnSetGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetGroupSizePrologue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetGroupSizePrologue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGroupSizeEpilogue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetGroupSizeEpilogue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    {
        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;

        if( nullptr == pfnSuggestGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSuggestGroupSizePrologue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSuggestGroupSizePrologue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestGroupSizeEpilogue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSuggestGroupSizeEpilogue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;

        if( nullptr == pfnSuggestMaxCooperativeGroupCount )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSuggestMaxCooperativeGroupCountPrologue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSuggestMaxCooperativeGroupCountPrologue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestMaxCooperativeGroupCountEpilogue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSuggestMaxCooperativeGroupCountEpilogue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;

        if( nullptr == pfnSetArgumentValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetArgumentValuePrologue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetArgumentValuePrologue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetArgumentValueEpilogue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetArgumentValueEpilogue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    {
        auto pfnSetIndirectAccess = context.zeDdiTable.Kernel.pfnSetIndirectAccess;

        if( nullptr == pfnSetIndirectAccess )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetIndirectAccessPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetIndirectAccessPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetIndirectAccessEpilogue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetIndirectAccess( hKernel, flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetIndirectAccessEpilogue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    {
        auto pfnGetIndirectAccess = context.zeDdiTable.Kernel.pfnGetIndirectAccess;

        if( nullptr == pfnGetIndirectAccess )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetIndirectAccessPrologue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetIndirectAccessPrologue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetIndirectAccessEpilogue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetIndirectAccess( hKernel, pFlags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetIndirectAccessEpilogue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetSourceAttributes
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetSourceAttributes(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes, including
                                                        ///< null-terminating character.
        char** pString                                  ///< [in,out][optional] pointer to application-managed character array
                                                        ///< (string data).
                                                        ///< If NULL, the string length of the kernel source attributes, including
                                                        ///< a null-terminating character, is returned in pSize.
                                                        ///< Otherwise, pString must point to valid application memory that is
                                                        ///< greater than or equal to *pSize bytes in length, and on return the
                                                        ///< pointed-to string will contain a space-separated list of kernel source attributes.
        )
    {
        auto pfnGetSourceAttributes = context.zeDdiTable.Kernel.pfnGetSourceAttributes;

        if( nullptr == pfnGetSourceAttributes )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetSourceAttributesPrologue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetSourceAttributesPrologue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetSourceAttributesEpilogue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetSourceAttributes( hKernel, pSize, pString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetSourceAttributesEpilogue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetCacheConfig
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    {
        auto pfnSetCacheConfig = context.zeDdiTable.Kernel.pfnSetCacheConfig;

        if( nullptr == pfnSetCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetCacheConfigPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetCacheConfigPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetCacheConfigEpilogue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetCacheConfig( hKernel, flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetCacheConfigEpilogue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetPropertiesPrologue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetPropertiesPrologue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetPropertiesEpilogue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetProperties( hKernel, pKernelProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetPropertiesEpilogue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetName
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetName(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    {
        auto pfnGetName = context.zeDdiTable.Kernel.pfnGetName;

        if( nullptr == pfnGetName )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetNamePrologue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetNamePrologue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetNameEpilogue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetName( hKernel, pSize, pName );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelGetNameEpilogue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;

        if( nullptr == pfnAppendLaunchKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;

        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchCooperativeKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchCooperativeKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchCooperativeKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchCooperativeKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;

        if( nullptr == pfnAppendLaunchKernelIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchKernelIndirectPrologue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchKernelIndirectPrologue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernelIndirectEpilogue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchKernelIndirectEpilogue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less than or equal to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;

        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeMemoryResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeMemoryResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        auto pfnMakeMemoryResident = context.zeDdiTable.Context.pfnMakeMemoryResident;

        if( nullptr == pfnMakeMemoryResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextMakeMemoryResidentPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextMakeMemoryResidentPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeMemoryResidentEpilogue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnMakeMemoryResident( hContext, hDevice, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextMakeMemoryResidentEpilogue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictMemory(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        auto pfnEvictMemory = context.zeDdiTable.Context.pfnEvictMemory;

        if( nullptr == pfnEvictMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextEvictMemoryPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextEvictMemoryPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictMemoryEpilogue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnEvictMemory( hContext, hDevice, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextEvictMemoryEpilogue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeImageResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeImageResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        auto pfnMakeImageResident = context.zeDdiTable.Context.pfnMakeImageResident;

        if( nullptr == pfnMakeImageResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextMakeImageResidentPrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextMakeImageResidentPrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeImageResidentEpilogue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnMakeImageResident( hContext, hDevice, hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextMakeImageResidentEpilogue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictImage
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictImage(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        auto pfnEvictImage = context.zeDdiTable.Context.pfnEvictImage;

        if( nullptr == pfnEvictImage )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextEvictImagePrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextEvictImagePrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictImageEpilogue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnEvictImage( hContext, hDevice, hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeContextEvictImageEpilogue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeSamplerCreatePrologue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeSamplerCreatePrologue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerCreateEpilogue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phSampler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeSamplerCreateEpilogue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phSampler){
                context.handleLifetime->addHandle( *phSampler );
                context.handleLifetime->addDependent( hContext, *phSampler );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeSamplerDestroyPrologue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeSamplerDestroyPrologue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerDestroyEpilogue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hSampler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeSamplerDestroyEpilogue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemReserve
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        auto pfnReserve = context.zeDdiTable.VirtualMem.pfnReserve;

        if( nullptr == pfnReserve )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemReservePrologue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemReservePrologue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemReserveEpilogue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnReserve( hContext, pStart, size, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemReserveEpilogue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    {
        auto pfnFree = context.zeDdiTable.VirtualMem.pfnFree;

        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemFreePrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemFreePrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemFreeEpilogue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnFree( hContext, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemFreeEpilogue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemQueryPageSize
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemQueryPageSize(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        )
    {
        auto pfnQueryPageSize = context.zeDdiTable.VirtualMem.pfnQueryPageSize;

        if( nullptr == pfnQueryPageSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemQueryPageSizePrologue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemQueryPageSizePrologue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemQueryPageSizeEpilogue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryPageSize( hContext, hDevice, size, pagesize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemQueryPageSizeEpilogue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemCreate
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        auto pfnCreate = context.zeDdiTable.PhysicalMem.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zePhysicalMemCreatePrologue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zePhysicalMemCreatePrologue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemCreateEpilogue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zePhysicalMemCreateEpilogue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phPhysicalMemory){
                context.handleLifetime->addHandle( *phPhysicalMemory );
                context.handleLifetime->addDependent( hContext, *phPhysicalMemory );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.PhysicalMem.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zePhysicalMemDestroyPrologue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zePhysicalMemDestroyPrologue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemDestroyEpilogue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroy( hContext, hPhysicalMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zePhysicalMemDestroyEpilogue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemMap
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemMap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
        size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                        ///< aligned.
        ze_physical_mem_handle_t hPhysicalMemory,       ///< [in] handle to physical memory object.
        size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                        ///< aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        auto pfnMap = context.zeDdiTable.VirtualMem.pfnMap;

        if( nullptr == pfnMap )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemMapPrologue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemMapPrologue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemMapEpilogue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemMapEpilogue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemUnmap
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemUnmap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    {
        auto pfnUnmap = context.zeDdiTable.VirtualMem.pfnUnmap;

        if( nullptr == pfnUnmap )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemUnmapPrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemUnmapPrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemUnmapEpilogue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnUnmap( hContext, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemUnmapEpilogue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemSetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemSetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        auto pfnSetAccessAttribute = context.zeDdiTable.VirtualMem.pfnSetAccessAttribute;

        if( nullptr == pfnSetAccessAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemSetAccessAttributePrologue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemSetAccessAttributePrologue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemSetAccessAttributeEpilogue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetAccessAttribute( hContext, ptr, size, access );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemSetAccessAttributeEpilogue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemGetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemGetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        )
    {
        auto pfnGetAccessAttribute = context.zeDdiTable.VirtualMem.pfnGetAccessAttribute;

        if( nullptr == pfnGetAccessAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemGetAccessAttributePrologue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemGetAccessAttributePrologue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemGetAccessAttributeEpilogue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetAccessAttribute( hContext, ptr, size, access, outSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeVirtualMemGetAccessAttributeEpilogue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGlobalOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGlobalOffsetExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        )
    {
        auto pfnSetGlobalOffsetExp = context.zeDdiTable.KernelExp.pfnSetGlobalOffsetExp;

        if( nullptr == pfnSetGlobalOffsetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetGlobalOffsetExpPrologue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetGlobalOffsetExpPrologue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGlobalOffsetExpEpilogue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSetGlobalOffsetExpEpilogue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceReserveCacheExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReserveCacheExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        )
    {
        auto pfnReserveCacheExt = context.zeDdiTable.Device.pfnReserveCacheExt;

        if( nullptr == pfnReserveCacheExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceReserveCacheExtPrologue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceReserveCacheExtPrologue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceReserveCacheExtEpilogue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceReserveCacheExtEpilogue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetCacheAdviceExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSetCacheAdviceExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        )
    {
        auto pfnSetCacheAdviceExt = context.zeDdiTable.Device.pfnSetCacheAdviceExt;

        if( nullptr == pfnSetCacheAdviceExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceSetCacheAdviceExtPrologue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceSetCacheAdviceExtPrologue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceSetCacheAdviceExtEpilogue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceSetCacheAdviceExtEpilogue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryTimestampsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryTimestampsExp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of timestamp results.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of timestamps available.
                                                        ///< if count is greater than the number of timestamps available, then the
                                                        ///< driver shall update the value with the correct number of timestamps available.
        ze_kernel_timestamp_result_t* pTimestamps       ///< [in,out][optional][range(0, *pCount)] array of timestamp results.
                                                        ///< if count is less than the number of timestamps available, then driver
                                                        ///< shall only retrieve that number of timestamps.
        )
    {
        auto pfnQueryTimestampsExp = context.zeDdiTable.EventExp.pfnQueryTimestampsExp;

        if( nullptr == pfnQueryTimestampsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryTimestampsExpPrologue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryTimestampsExpPrologue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryTimestampsExpEpilogue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryTimestampsExpEpilogue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetMemoryPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    {
        auto pfnGetMemoryPropertiesExp = context.zeDdiTable.ImageExp.pfnGetMemoryPropertiesExp;

        if( nullptr == pfnGetMemoryPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetMemoryPropertiesExpPrologue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetMemoryPropertiesExpPrologue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetMemoryPropertiesExpEpilogue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetMemoryPropertiesExpEpilogue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        auto pfnViewCreateExt = context.zeDdiTable.Image.pfnViewCreateExt;

        if( nullptr == pfnViewCreateExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageViewCreateExtPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageViewCreateExtPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExtEpilogue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageViewCreateExtEpilogue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        auto pfnViewCreateExp = context.zeDdiTable.ImageExp.pfnViewCreateExp;

        if( nullptr == pfnViewCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageViewCreateExpPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageViewCreateExpPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExpEpilogue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageViewCreateExpEpilogue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSchedulingHintExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    {
        auto pfnSchedulingHintExp = context.zeDdiTable.KernelExp.pfnSchedulingHintExp;

        if( nullptr == pfnSchedulingHintExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSchedulingHintExpPrologue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSchedulingHintExpPrologue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSchedulingHintExpEpilogue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnSchedulingHintExp( hKernel, pHint );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeKernelSchedulingHintExpEpilogue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDevicePciGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    {
        auto pfnPciGetPropertiesExt = context.zeDdiTable.Device.pfnPciGetPropertiesExt;

        if( nullptr == pfnPciGetPropertiesExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDevicePciGetPropertiesExtPrologue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDevicePciGetPropertiesExtPrologue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDevicePciGetPropertiesExtEpilogue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnPciGetPropertiesExt( hDevice, pPciProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDevicePciGetPropertiesExtEpilogue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        uint32_t destRowPitch,                          ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being written
        uint32_t destSlicePitch,                        ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being written
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopyToMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemoryExt;

        if( nullptr == pfnAppendImageCopyToMemoryExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyToMemoryExtPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyToMemoryExtPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemoryExtEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyToMemoryExtEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        uint32_t srcRowPitch,                           ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being read
        uint32_t srcSlicePitch,                         ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being read
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnAppendImageCopyFromMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemoryExt;

        if( nullptr == pfnAppendImageCopyFromMemoryExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyFromMemoryExtPrologue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyFromMemoryExtPrologue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemoryExtEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListAppendImageCopyFromMemoryExtEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetAllocPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetAllocPropertiesExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        )
    {
        auto pfnGetAllocPropertiesExt = context.zeDdiTable.Image.pfnGetAllocPropertiesExt;

        if( nullptr == pfnGetAllocPropertiesExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetAllocPropertiesExtPrologue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetAllocPropertiesExtPrologue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetAllocPropertiesExtEpilogue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetAllocPropertiesExtEpilogue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleInspectLinkageExt
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleInspectLinkageExt(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        )
    {
        auto pfnInspectLinkageExt = context.zeDdiTable.Module.pfnInspectLinkageExt;

        if( nullptr == pfnInspectLinkageExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleInspectLinkageExtPrologue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleInspectLinkageExtPrologue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleInspectLinkageExtEpilogue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeModuleInspectLinkageExtEpilogue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFreeExt
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFreeExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto pfnFreeExt = context.zeDdiTable.Mem.pfnFreeExt;

        if( nullptr == pfnFreeExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemFreeExtPrologue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemFreeExtPrologue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFreeExtEpilogue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnFreeExt( hContext, pMemFreeDesc, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemFreeExtEpilogue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric vertices available.
                                                        ///< if count is greater than the number of fabric vertices available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< vertices available.
        ze_fabric_vertex_handle_t* phVertices           ///< [in,out][optional][range(0, *pCount)] array of handle of fabric vertices.
                                                        ///< if count is less than the number of fabric vertices available, then
                                                        ///< driver shall only retrieve that number of fabric vertices.
        )
    {
        auto pfnGetExp = context.zeDdiTable.FabricVertexExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetExpPrologue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetExpPrologue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetExpEpilogue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetExp( hDriver, pCount, phVertices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetExpEpilogue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phVertices) && (i < *pCount); ++i){
                if (phVertices[i]){
                    context.handleLifetime->addHandle( phVertices[i] );
                    context.handleLifetime->addDependent( hDriver, phVertices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetSubVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetSubVerticesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-vertices available.
                                                        ///< if count is greater than the number of sub-vertices available, then
                                                        ///< the driver shall update the value with the correct number of
                                                        ///< sub-vertices available.
        ze_fabric_vertex_handle_t* phSubvertices        ///< [in,out][optional][range(0, *pCount)] array of handle of sub-vertices.
                                                        ///< if count is less than the number of sub-vertices available, then
                                                        ///< driver shall only retrieve that number of sub-vertices.
        )
    {
        auto pfnGetSubVerticesExp = context.zeDdiTable.FabricVertexExp.pfnGetSubVerticesExp;

        if( nullptr == pfnGetSubVerticesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetSubVerticesExpPrologue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetSubVerticesExpPrologue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetSubVerticesExpEpilogue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetSubVerticesExpEpilogue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubvertices) && (i < *pCount); ++i){
                if (phSubvertices[i]){
                    context.handleLifetime->addHandle( phSubvertices[i] );
                    context.handleLifetime->addDependent( hVertex, phSubvertices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.FabricVertexExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetPropertiesExpPrologue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetPropertiesExpPrologue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetPropertiesExpEpilogue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetPropertiesExp( hVertex, pVertexProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetPropertiesExpEpilogue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetDeviceExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    {
        auto pfnGetDeviceExp = context.zeDdiTable.FabricVertexExp.pfnGetDeviceExp;

        if( nullptr == pfnGetDeviceExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetDeviceExpPrologue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetDeviceExpPrologue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetDeviceExpEpilogue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetDeviceExp( hVertex, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricVertexGetDeviceExpEpilogue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phDevice){
                context.handleLifetime->addHandle( *phDevice );
                context.handleLifetime->addDependent( hVertex, *phDevice );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetFabricVertexExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    {
        auto pfnGetFabricVertexExp = context.zeDdiTable.DeviceExp.pfnGetFabricVertexExp;

        if( nullptr == pfnGetFabricVertexExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetFabricVertexExpPrologue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetFabricVertexExpPrologue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetFabricVertexExpEpilogue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetFabricVertexExp( hDevice, phVertex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDeviceGetFabricVertexExpEpilogue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertex){
                context.handleLifetime->addHandle( *phVertex );
                context.handleLifetime->addDependent( hDevice, *phVertex );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetExp(
        ze_fabric_vertex_handle_t hVertexA,             ///< [in] handle of first fabric vertex instance
        ze_fabric_vertex_handle_t hVertexB,             ///< [in] handle of second fabric vertex instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric edges.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric edges available.
                                                        ///< if count is greater than the number of fabric edges available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< edges available.
        ze_fabric_edge_handle_t* phEdges                ///< [in,out][optional][range(0, *pCount)] array of handle of fabric edges.
                                                        ///< if count is less than the number of fabric edges available, then
                                                        ///< driver shall only retrieve that number of fabric edges.
        )
    {
        auto pfnGetExp = context.zeDdiTable.FabricEdgeExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetExpPrologue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetExpPrologue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetExpEpilogue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetExp( hVertexA, hVertexB, pCount, phEdges );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetExpEpilogue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phEdges) && (i < *pCount); ++i){
                if (phEdges[i]){
                    context.handleLifetime->addHandle( phEdges[i] );
                    context.handleLifetime->addDependent( hVertexA, phEdges[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetVerticesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        )
    {
        auto pfnGetVerticesExp = context.zeDdiTable.FabricEdgeExp.pfnGetVerticesExp;

        if( nullptr == pfnGetVerticesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetVerticesExpPrologue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetVerticesExpPrologue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetVerticesExpEpilogue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetVerticesExp( hEdge, phVertexA, phVertexB );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetVerticesExpEpilogue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertexA){
                context.handleLifetime->addHandle( *phVertexA );
                context.handleLifetime->addDependent( hEdge, *phVertexA );

            }
            if (phVertexB){
                context.handleLifetime->addHandle( *phVertexB );
                context.handleLifetime->addDependent( hEdge, *phVertexB );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.FabricEdgeExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetPropertiesExpPrologue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetPropertiesExpPrologue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetPropertiesExpEpilogue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetPropertiesExp( hEdge, pEdgeProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeFabricEdgeGetPropertiesExpEpilogue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestampsExt
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestampsExt(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of event packets available.
                                                        ///<    - This value is implementation specific.
                                                        ///<    - if `*pCount` is zero, then the driver shall update the value with
                                                        ///< the total number of event packets available.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver shall update the value with the correct value.
                                                        ///<    - Buffer(s) for query results must be sized by the application to
                                                        ///< accommodate a minimum of `*pCount` elements.
        ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ///< [in,out][optional][range(0, *pCount)] pointer to event query
                                                        ///< properties structure(s).
                                                        ///<    - This parameter may be null when `*pCount` is zero.
                                                        ///<    - if `*pCount` is less than the number of event packets available,
                                                        ///< the driver may only update `*pCount` elements, starting at element zero.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver may only update the valid elements.
        )
    {
        auto pfnQueryKernelTimestampsExt = context.zeDdiTable.Event.pfnQueryKernelTimestampsExt;

        if( nullptr == pfnQueryKernelTimestampsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryKernelTimestampsExtPrologue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryKernelTimestampsExtPrologue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestampsExtEpilogue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeEventQueryKernelTimestampsExtEpilogue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        auto pfnCreateExp = context.zeDdiTable.RTASBuilderExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderCreateExpPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderCreateExpPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderCreateExpEpilogue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreateExp( hDriver, pDescriptor, phBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderCreateExpEpilogue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phBuilder){
                context.handleLifetime->addHandle( *phBuilder );
                context.handleLifetime->addDependent( hDriver, *phBuilder );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderGetBuildPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        auto pfnGetBuildPropertiesExp = context.zeDdiTable.RTASBuilderExp.pfnGetBuildPropertiesExp;

        if( nullptr == pfnGetBuildPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderGetBuildPropertiesExpPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderGetBuildPropertiesExpPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderGetBuildPropertiesExpEpilogue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderGetBuildPropertiesExpEpilogue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverRTASFormatCompatibilityCheckExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        )
    {
        auto pfnRTASFormatCompatibilityCheckExp = context.zeDdiTable.DriverExp.pfnRTASFormatCompatibilityCheckExp;

        if( nullptr == pfnRTASFormatCompatibilityCheckExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverRTASFormatCompatibilityCheckExpPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverRTASFormatCompatibilityCheckExpPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverRTASFormatCompatibilityCheckExpEpilogue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeDriverRTASFormatCompatibilityCheckExpEpilogue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderBuildExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderBuildExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                        ///< during acceleration structure construction
        size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
        void* pRtasBuffer,                              ///< [in] pointer to destination buffer
        size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
        void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
        ze_rtas_aabb_exp_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                        ///< structure bounds
        size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                        ///< bytes
        )
    {
        auto pfnBuildExp = context.zeDdiTable.RTASBuilderExp.pfnBuildExp;

        if( nullptr == pfnBuildExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderBuildExpPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderBuildExpPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderBuildExpEpilogue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderBuildExpEpilogue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        auto pfnDestroyExp = context.zeDdiTable.RTASBuilderExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderDestroyExpPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderDestroyExpPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderDestroyExpEpilogue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroyExp( hBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASBuilderDestroyExpEpilogue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        auto pfnCreateExp = context.zeDdiTable.RTASParallelOperationExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationCreateExpPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationCreateExpPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationCreateExpEpilogue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreateExp( hDriver, phParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationCreateExpEpilogue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phParallelOperation){
                context.handleLifetime->addHandle( *phParallelOperation );
                context.handleLifetime->addDependent( hDriver, *phParallelOperation );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.RTASParallelOperationExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationGetPropertiesExpPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationGetPropertiesExpPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationGetPropertiesExpEpilogue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetPropertiesExp( hParallelOperation, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationGetPropertiesExpEpilogue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        auto pfnJoinExp = context.zeDdiTable.RTASParallelOperationExp.pfnJoinExp;

        if( nullptr == pfnJoinExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationJoinExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationJoinExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationJoinExpEpilogue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnJoinExp( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationJoinExpEpilogue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        auto pfnDestroyExp = context.zeDdiTable.RTASParallelOperationExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationDestroyExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationDestroyExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationDestroyExpEpilogue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnDestroyExp( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeRTASParallelOperationDestroyExpEpilogue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetPitchFor2dImage
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetPitchFor2dImage(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        size_t imageWidth,                              ///< [in] imageWidth
        size_t imageHeight,                             ///< [in] imageHeight
        unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
        size_t * rowPitch                               ///< [out] rowPitch
        )
    {
        auto pfnGetPitchFor2dImage = context.zeDdiTable.Mem.pfnGetPitchFor2dImage;

        if( nullptr == pfnGetPitchFor2dImage )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetPitchFor2dImagePrologue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetPitchFor2dImagePrologue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetPitchFor2dImageEpilogue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetPitchFor2dImage( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeMemGetPitchFor2dImageEpilogue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetDeviceOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetDeviceOffsetExp(
        ze_image_handle_t hImage,                       ///< [in] handle of the image
        uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
        )
    {
        auto pfnGetDeviceOffsetExp = context.zeDdiTable.ImageExp.pfnGetDeviceOffsetExp;

        if( nullptr == pfnGetDeviceOffsetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetDeviceOffsetExpPrologue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetDeviceOffsetExpPrologue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetDeviceOffsetExpEpilogue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetDeviceOffsetExp( hImage, pDeviceOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeImageGetDeviceOffsetExpEpilogue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateCloneExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateCloneExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
        ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
        )
    {
        auto pfnCreateCloneExp = context.zeDdiTable.CommandListExp.pfnCreateCloneExp;

        if( nullptr == pfnCreateCloneExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreateCloneExpPrologue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListCreateCloneExpPrologue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateCloneExpEpilogue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnCreateCloneExp( hCommandList, phClonedCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListCreateCloneExpEpilogue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phClonedCommandList){
                context.handleLifetime->addHandle( *phClonedCommandList );
                context.handleLifetime->addDependent( hCommandList, *phClonedCommandList );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateAppendCommandListsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateAppendCommandListsExp(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t numCommandLists,                       ///< [in] number of command lists
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                        ///<    - if not null, this event is signaled after the completion of all
                                                        ///< appended command lists
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                        ///< command lists; must be 0 if nullptr == phWaitEvents
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing appended command lists.
                                                        ///<    - if not null, all wait events must be satisfied prior to the start
                                                        ///< of any appended command list(s)
        )
    {
        auto pfnImmediateAppendCommandListsExp = context.zeDdiTable.CommandListExp.pfnImmediateAppendCommandListsExp;

        if( nullptr == pfnImmediateAppendCommandListsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListImmediateAppendCommandListsExpPrologue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListImmediateAppendCommandListsExpPrologue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListImmediateAppendCommandListsExpEpilogue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnImmediateAppendCommandListsExp( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListImmediateAppendCommandListsExpEpilogue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetNextCommandIdExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        )
    {
        auto pfnGetNextCommandIdExp = context.zeDdiTable.CommandListExp.pfnGetNextCommandIdExp;

        if( nullptr == pfnGetNextCommandIdExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetNextCommandIdExpPrologue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListGetNextCommandIdExpPrologue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetNextCommandIdExpEpilogue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnGetNextCommandIdExp( hCommandList, desc, pCommandId );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListGetNextCommandIdExpEpilogue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                        ///< be chained via `pNext` member
        )
    {
        auto pfnUpdateMutableCommandsExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandsExp;

        if( nullptr == pfnUpdateMutableCommandsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandsExpPrologue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListUpdateMutableCommandsExpPrologue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandsExpEpilogue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnUpdateMutableCommandsExp( hCommandList, desc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandsExpEpilogue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandSignalEventExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandSignalEventExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
        )
    {
        auto pfnUpdateMutableCommandSignalEventExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandSignalEventExp;

        if( nullptr == pfnUpdateMutableCommandSignalEventExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandSignalEventExpPrologue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListUpdateMutableCommandSignalEventExpPrologue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandSignalEventExpEpilogue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnUpdateMutableCommandSignalEventExp( hCommandList, commandId, hSignalEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandSignalEventExpEpilogue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandWaitEventsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandWaitEventsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        auto pfnUpdateMutableCommandWaitEventsExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandWaitEventsExp;

        if( nullptr == pfnUpdateMutableCommandWaitEventsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandWaitEventsExpPrologue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListUpdateMutableCommandWaitEventsExpPrologue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandWaitEventsExpEpilogue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        auto result = pfnUpdateMutableCommandWaitEventsExp( hCommandList, commandId, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeParamValidation->zeCommandListUpdateMutableCommandWaitEventsExpEpilogue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }

        return result;
    }

} // namespace validation_layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = validation_layer::zeInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASBuilderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASBuilderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_builder_exp_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASBuilderExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
    pDdiTable->pfnCreateExp                              = validation_layer::zeRTASBuilderCreateExp;

    dditable.pfnGetBuildPropertiesExp                    = pDdiTable->pfnGetBuildPropertiesExp;
    pDdiTable->pfnGetBuildPropertiesExp                  = validation_layer::zeRTASBuilderGetBuildPropertiesExp;

    dditable.pfnBuildExp                                 = pDdiTable->pfnBuildExp;
    pDdiTable->pfnBuildExp                               = validation_layer::zeRTASBuilderBuildExp;

    dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
    pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASBuilderDestroyExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASParallelOperationExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASParallelOperationExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_parallel_operation_exp_dditable_t* pDdiTable///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASParallelOperationExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
    pDdiTable->pfnCreateExp                              = validation_layer::zeRTASParallelOperationCreateExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeRTASParallelOperationGetPropertiesExp;

    dditable.pfnJoinExp                                  = pDdiTable->pfnJoinExp;
    pDdiTable->pfnJoinExp                                = validation_layer::zeRTASParallelOperationJoinExp;

    dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
    pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASParallelOperationDestroyExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Driver;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zeDriverGet;

    dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
    pDdiTable->pfnGetApiVersion                          = validation_layer::zeDriverGetApiVersion;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeDriverGetProperties;

    dditable.pfnGetIpcProperties                         = pDdiTable->pfnGetIpcProperties;
    pDdiTable->pfnGetIpcProperties                       = validation_layer::zeDriverGetIpcProperties;

    dditable.pfnGetExtensionProperties                   = pDdiTable->pfnGetExtensionProperties;
    pDdiTable->pfnGetExtensionProperties                 = validation_layer::zeDriverGetExtensionProperties;

    dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
    pDdiTable->pfnGetExtensionFunctionAddress            = validation_layer::zeDriverGetExtensionFunctionAddress;

    dditable.pfnGetLastErrorDescription                  = pDdiTable->pfnGetLastErrorDescription;
    pDdiTable->pfnGetLastErrorDescription                = validation_layer::zeDriverGetLastErrorDescription;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DriverExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.DriverExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnRTASFormatCompatibilityCheckExp          = pDdiTable->pfnRTASFormatCompatibilityCheckExp;
    pDdiTable->pfnRTASFormatCompatibilityCheckExp        = validation_layer::zeDriverRTASFormatCompatibilityCheckExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zeDeviceGet;

    dditable.pfnGetSubDevices                            = pDdiTable->pfnGetSubDevices;
    pDdiTable->pfnGetSubDevices                          = validation_layer::zeDeviceGetSubDevices;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeDeviceGetProperties;

    dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
    pDdiTable->pfnGetComputeProperties                   = validation_layer::zeDeviceGetComputeProperties;

    dditable.pfnGetModuleProperties                      = pDdiTable->pfnGetModuleProperties;
    pDdiTable->pfnGetModuleProperties                    = validation_layer::zeDeviceGetModuleProperties;

    dditable.pfnGetCommandQueueGroupProperties           = pDdiTable->pfnGetCommandQueueGroupProperties;
    pDdiTable->pfnGetCommandQueueGroupProperties         = validation_layer::zeDeviceGetCommandQueueGroupProperties;

    dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
    pDdiTable->pfnGetMemoryProperties                    = validation_layer::zeDeviceGetMemoryProperties;

    dditable.pfnGetMemoryAccessProperties                = pDdiTable->pfnGetMemoryAccessProperties;
    pDdiTable->pfnGetMemoryAccessProperties              = validation_layer::zeDeviceGetMemoryAccessProperties;

    dditable.pfnGetCacheProperties                       = pDdiTable->pfnGetCacheProperties;
    pDdiTable->pfnGetCacheProperties                     = validation_layer::zeDeviceGetCacheProperties;

    dditable.pfnGetImageProperties                       = pDdiTable->pfnGetImageProperties;
    pDdiTable->pfnGetImageProperties                     = validation_layer::zeDeviceGetImageProperties;

    dditable.pfnGetExternalMemoryProperties              = pDdiTable->pfnGetExternalMemoryProperties;
    pDdiTable->pfnGetExternalMemoryProperties            = validation_layer::zeDeviceGetExternalMemoryProperties;

    dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
    pDdiTable->pfnGetP2PProperties                       = validation_layer::zeDeviceGetP2PProperties;

    dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
    pDdiTable->pfnCanAccessPeer                          = validation_layer::zeDeviceCanAccessPeer;

    dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
    pDdiTable->pfnGetStatus                              = validation_layer::zeDeviceGetStatus;

    dditable.pfnGetGlobalTimestamps                      = pDdiTable->pfnGetGlobalTimestamps;
    pDdiTable->pfnGetGlobalTimestamps                    = validation_layer::zeDeviceGetGlobalTimestamps;

    dditable.pfnReserveCacheExt                          = pDdiTable->pfnReserveCacheExt;
    pDdiTable->pfnReserveCacheExt                        = validation_layer::zeDeviceReserveCacheExt;

    dditable.pfnSetCacheAdviceExt                        = pDdiTable->pfnSetCacheAdviceExt;
    pDdiTable->pfnSetCacheAdviceExt                      = validation_layer::zeDeviceSetCacheAdviceExt;

    dditable.pfnPciGetPropertiesExt                      = pDdiTable->pfnPciGetPropertiesExt;
    pDdiTable->pfnPciGetPropertiesExt                    = validation_layer::zeDevicePciGetPropertiesExt;

    dditable.pfnGetRootDevice                            = pDdiTable->pfnGetRootDevice;
    pDdiTable->pfnGetRootDevice                          = validation_layer::zeDeviceGetRootDevice;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.DeviceExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetFabricVertexExp                       = pDdiTable->pfnGetFabricVertexExp;
    pDdiTable->pfnGetFabricVertexExp                     = validation_layer::zeDeviceGetFabricVertexExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_context_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Context;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeContextCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeContextDestroy;

    dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
    pDdiTable->pfnGetStatus                              = validation_layer::zeContextGetStatus;

    dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
    pDdiTable->pfnSystemBarrier                          = validation_layer::zeContextSystemBarrier;

    dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
    pDdiTable->pfnMakeMemoryResident                     = validation_layer::zeContextMakeMemoryResident;

    dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
    pDdiTable->pfnEvictMemory                            = validation_layer::zeContextEvictMemory;

    dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
    pDdiTable->pfnMakeImageResident                      = validation_layer::zeContextMakeImageResident;

    dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
    pDdiTable->pfnEvictImage                             = validation_layer::zeContextEvictImage;

    dditable.pfnCreateEx                                 = pDdiTable->pfnCreateEx;
    pDdiTable->pfnCreateEx                               = validation_layer::zeContextCreateEx;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandQueue;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeCommandQueueCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeCommandQueueDestroy;

    dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
    pDdiTable->pfnExecuteCommandLists                    = validation_layer::zeCommandQueueExecuteCommandLists;

    dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
    pDdiTable->pfnSynchronize                            = validation_layer::zeCommandQueueSynchronize;

    dditable.pfnGetOrdinal                               = pDdiTable->pfnGetOrdinal;
    pDdiTable->pfnGetOrdinal                             = validation_layer::zeCommandQueueGetOrdinal;

    dditable.pfnGetIndex                                 = pDdiTable->pfnGetIndex;
    pDdiTable->pfnGetIndex                               = validation_layer::zeCommandQueueGetIndex;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeCommandListCreate;

    dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
    pDdiTable->pfnCreateImmediate                        = validation_layer::zeCommandListCreateImmediate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeCommandListDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = validation_layer::zeCommandListClose;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zeCommandListReset;

    dditable.pfnAppendWriteGlobalTimestamp               = pDdiTable->pfnAppendWriteGlobalTimestamp;
    pDdiTable->pfnAppendWriteGlobalTimestamp             = validation_layer::zeCommandListAppendWriteGlobalTimestamp;

    dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
    pDdiTable->pfnAppendBarrier                          = validation_layer::zeCommandListAppendBarrier;

    dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier              = validation_layer::zeCommandListAppendMemoryRangesBarrier;

    dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopy                       = validation_layer::zeCommandListAppendMemoryCopy;

    dditable.pfnAppendMemoryFill                         = pDdiTable->pfnAppendMemoryFill;
    pDdiTable->pfnAppendMemoryFill                       = validation_layer::zeCommandListAppendMemoryFill;

    dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryCopyRegion                 = validation_layer::zeCommandListAppendMemoryCopyRegion;

    dditable.pfnAppendMemoryCopyFromContext              = pDdiTable->pfnAppendMemoryCopyFromContext;
    pDdiTable->pfnAppendMemoryCopyFromContext            = validation_layer::zeCommandListAppendMemoryCopyFromContext;

    dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
    pDdiTable->pfnAppendImageCopy                        = validation_layer::zeCommandListAppendImageCopy;

    dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyRegion                  = validation_layer::zeCommandListAppendImageCopyRegion;

    dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyToMemory                = validation_layer::zeCommandListAppendImageCopyToMemory;

    dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
    pDdiTable->pfnAppendImageCopyFromMemory              = validation_layer::zeCommandListAppendImageCopyFromMemory;

    dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemoryPrefetch                   = validation_layer::zeCommandListAppendMemoryPrefetch;

    dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
    pDdiTable->pfnAppendMemAdvise                        = validation_layer::zeCommandListAppendMemAdvise;

    dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
    pDdiTable->pfnAppendSignalEvent                      = validation_layer::zeCommandListAppendSignalEvent;

    dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
    pDdiTable->pfnAppendWaitOnEvents                     = validation_layer::zeCommandListAppendWaitOnEvents;

    dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
    pDdiTable->pfnAppendEventReset                       = validation_layer::zeCommandListAppendEventReset;

    dditable.pfnAppendQueryKernelTimestamps              = pDdiTable->pfnAppendQueryKernelTimestamps;
    pDdiTable->pfnAppendQueryKernelTimestamps            = validation_layer::zeCommandListAppendQueryKernelTimestamps;

    dditable.pfnAppendLaunchKernel                       = pDdiTable->pfnAppendLaunchKernel;
    pDdiTable->pfnAppendLaunchKernel                     = validation_layer::zeCommandListAppendLaunchKernel;

    dditable.pfnAppendLaunchCooperativeKernel            = pDdiTable->pfnAppendLaunchCooperativeKernel;
    pDdiTable->pfnAppendLaunchCooperativeKernel          = validation_layer::zeCommandListAppendLaunchCooperativeKernel;

    dditable.pfnAppendLaunchKernelIndirect               = pDdiTable->pfnAppendLaunchKernelIndirect;
    pDdiTable->pfnAppendLaunchKernelIndirect             = validation_layer::zeCommandListAppendLaunchKernelIndirect;

    dditable.pfnAppendLaunchMultipleKernelsIndirect      = pDdiTable->pfnAppendLaunchMultipleKernelsIndirect;
    pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = validation_layer::zeCommandListAppendLaunchMultipleKernelsIndirect;

    dditable.pfnAppendImageCopyToMemoryExt               = pDdiTable->pfnAppendImageCopyToMemoryExt;
    pDdiTable->pfnAppendImageCopyToMemoryExt             = validation_layer::zeCommandListAppendImageCopyToMemoryExt;

    dditable.pfnAppendImageCopyFromMemoryExt             = pDdiTable->pfnAppendImageCopyFromMemoryExt;
    pDdiTable->pfnAppendImageCopyFromMemoryExt           = validation_layer::zeCommandListAppendImageCopyFromMemoryExt;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeCommandListHostSynchronize;

    dditable.pfnGetDeviceHandle                          = pDdiTable->pfnGetDeviceHandle;
    pDdiTable->pfnGetDeviceHandle                        = validation_layer::zeCommandListGetDeviceHandle;

    dditable.pfnGetContextHandle                         = pDdiTable->pfnGetContextHandle;
    pDdiTable->pfnGetContextHandle                       = validation_layer::zeCommandListGetContextHandle;

    dditable.pfnGetOrdinal                               = pDdiTable->pfnGetOrdinal;
    pDdiTable->pfnGetOrdinal                             = validation_layer::zeCommandListGetOrdinal;

    dditable.pfnImmediateGetIndex                        = pDdiTable->pfnImmediateGetIndex;
    pDdiTable->pfnImmediateGetIndex                      = validation_layer::zeCommandListImmediateGetIndex;

    dditable.pfnIsImmediate                              = pDdiTable->pfnIsImmediate;
    pDdiTable->pfnIsImmediate                            = validation_layer::zeCommandListIsImmediate;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandListExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_exp_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandListExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreateCloneExp                           = pDdiTable->pfnCreateCloneExp;
    pDdiTable->pfnCreateCloneExp                         = validation_layer::zeCommandListCreateCloneExp;

    dditable.pfnImmediateAppendCommandListsExp           = pDdiTable->pfnImmediateAppendCommandListsExp;
    pDdiTable->pfnImmediateAppendCommandListsExp         = validation_layer::zeCommandListImmediateAppendCommandListsExp;

    dditable.pfnGetNextCommandIdExp                      = pDdiTable->pfnGetNextCommandIdExp;
    pDdiTable->pfnGetNextCommandIdExp                    = validation_layer::zeCommandListGetNextCommandIdExp;

    dditable.pfnUpdateMutableCommandsExp                 = pDdiTable->pfnUpdateMutableCommandsExp;
    pDdiTable->pfnUpdateMutableCommandsExp               = validation_layer::zeCommandListUpdateMutableCommandsExp;

    dditable.pfnUpdateMutableCommandSignalEventExp       = pDdiTable->pfnUpdateMutableCommandSignalEventExp;
    pDdiTable->pfnUpdateMutableCommandSignalEventExp     = validation_layer::zeCommandListUpdateMutableCommandSignalEventExp;

    dditable.pfnUpdateMutableCommandWaitEventsExp        = pDdiTable->pfnUpdateMutableCommandWaitEventsExp;
    pDdiTable->pfnUpdateMutableCommandWaitEventsExp      = validation_layer::zeCommandListUpdateMutableCommandWaitEventsExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Event;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeEventCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeEventDestroy;

    dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
    pDdiTable->pfnHostSignal                             = validation_layer::zeEventHostSignal;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeEventHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = validation_layer::zeEventQueryStatus;

    dditable.pfnHostReset                                = pDdiTable->pfnHostReset;
    pDdiTable->pfnHostReset                              = validation_layer::zeEventHostReset;

    dditable.pfnQueryKernelTimestamp                     = pDdiTable->pfnQueryKernelTimestamp;
    pDdiTable->pfnQueryKernelTimestamp                   = validation_layer::zeEventQueryKernelTimestamp;

    dditable.pfnQueryKernelTimestampsExt                 = pDdiTable->pfnQueryKernelTimestampsExt;
    pDdiTable->pfnQueryKernelTimestampsExt               = validation_layer::zeEventQueryKernelTimestampsExt;

    dditable.pfnGetEventPool                             = pDdiTable->pfnGetEventPool;
    pDdiTable->pfnGetEventPool                           = validation_layer::zeEventGetEventPool;

    dditable.pfnGetSignalScope                           = pDdiTable->pfnGetSignalScope;
    pDdiTable->pfnGetSignalScope                         = validation_layer::zeEventGetSignalScope;

    dditable.pfnGetWaitScope                             = pDdiTable->pfnGetWaitScope;
    pDdiTable->pfnGetWaitScope                           = validation_layer::zeEventGetWaitScope;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.EventExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnQueryTimestampsExp                       = pDdiTable->pfnQueryTimestampsExp;
    pDdiTable->pfnQueryTimestampsExp                     = validation_layer::zeEventQueryTimestampsExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.EventPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeEventPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeEventPoolDestroy;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = validation_layer::zeEventPoolGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeEventPoolOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeEventPoolCloseIpcHandle;

    dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
    pDdiTable->pfnPutIpcHandle                           = validation_layer::zeEventPoolPutIpcHandle;

    dditable.pfnGetContextHandle                         = pDdiTable->pfnGetContextHandle;
    pDdiTable->pfnGetContextHandle                       = validation_layer::zeEventPoolGetContextHandle;

    dditable.pfnGetFlags                                 = pDdiTable->pfnGetFlags;
    pDdiTable->pfnGetFlags                               = validation_layer::zeEventPoolGetFlags;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Fence;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeFenceCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeFenceDestroy;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeFenceHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = validation_layer::zeFenceQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zeFenceReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Image;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeImageGetProperties;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeImageCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeImageDestroy;

    dditable.pfnGetAllocPropertiesExt                    = pDdiTable->pfnGetAllocPropertiesExt;
    pDdiTable->pfnGetAllocPropertiesExt                  = validation_layer::zeImageGetAllocPropertiesExt;

    dditable.pfnViewCreateExt                            = pDdiTable->pfnViewCreateExt;
    pDdiTable->pfnViewCreateExt                          = validation_layer::zeImageViewCreateExt;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ImageExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.ImageExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetMemoryPropertiesExp                   = pDdiTable->pfnGetMemoryPropertiesExp;
    pDdiTable->pfnGetMemoryPropertiesExp                 = validation_layer::zeImageGetMemoryPropertiesExp;

    dditable.pfnViewCreateExp                            = pDdiTable->pfnViewCreateExp;
    pDdiTable->pfnViewCreateExp                          = validation_layer::zeImageViewCreateExp;

    dditable.pfnGetDeviceOffsetExp                       = pDdiTable->pfnGetDeviceOffsetExp;
    pDdiTable->pfnGetDeviceOffsetExp                     = validation_layer::zeImageGetDeviceOffsetExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeKernelCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeKernelDestroy;

    dditable.pfnSetCacheConfig                           = pDdiTable->pfnSetCacheConfig;
    pDdiTable->pfnSetCacheConfig                         = validation_layer::zeKernelSetCacheConfig;

    dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
    pDdiTable->pfnSetGroupSize                           = validation_layer::zeKernelSetGroupSize;

    dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
    pDdiTable->pfnSuggestGroupSize                       = validation_layer::zeKernelSuggestGroupSize;

    dditable.pfnSuggestMaxCooperativeGroupCount          = pDdiTable->pfnSuggestMaxCooperativeGroupCount;
    pDdiTable->pfnSuggestMaxCooperativeGroupCount        = validation_layer::zeKernelSuggestMaxCooperativeGroupCount;

    dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
    pDdiTable->pfnSetArgumentValue                       = validation_layer::zeKernelSetArgumentValue;

    dditable.pfnSetIndirectAccess                        = pDdiTable->pfnSetIndirectAccess;
    pDdiTable->pfnSetIndirectAccess                      = validation_layer::zeKernelSetIndirectAccess;

    dditable.pfnGetIndirectAccess                        = pDdiTable->pfnGetIndirectAccess;
    pDdiTable->pfnGetIndirectAccess                      = validation_layer::zeKernelGetIndirectAccess;

    dditable.pfnGetSourceAttributes                      = pDdiTable->pfnGetSourceAttributes;
    pDdiTable->pfnGetSourceAttributes                    = validation_layer::zeKernelGetSourceAttributes;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeKernelGetProperties;

    dditable.pfnGetName                                  = pDdiTable->pfnGetName;
    pDdiTable->pfnGetName                                = validation_layer::zeKernelGetName;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's KernelExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.KernelExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnSetGlobalOffsetExp                       = pDdiTable->pfnSetGlobalOffsetExp;
    pDdiTable->pfnSetGlobalOffsetExp                     = validation_layer::zeKernelSetGlobalOffsetExp;

    dditable.pfnSchedulingHintExp                        = pDdiTable->pfnSchedulingHintExp;
    pDdiTable->pfnSchedulingHintExp                      = validation_layer::zeKernelSchedulingHintExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Mem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_dditable_t* pDdiTable                    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Mem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAllocShared                              = pDdiTable->pfnAllocShared;
    pDdiTable->pfnAllocShared                            = validation_layer::zeMemAllocShared;

    dditable.pfnAllocDevice                              = pDdiTable->pfnAllocDevice;
    pDdiTable->pfnAllocDevice                            = validation_layer::zeMemAllocDevice;

    dditable.pfnAllocHost                                = pDdiTable->pfnAllocHost;
    pDdiTable->pfnAllocHost                              = validation_layer::zeMemAllocHost;

    dditable.pfnFree                                     = pDdiTable->pfnFree;
    pDdiTable->pfnFree                                   = validation_layer::zeMemFree;

    dditable.pfnGetAllocProperties                       = pDdiTable->pfnGetAllocProperties;
    pDdiTable->pfnGetAllocProperties                     = validation_layer::zeMemGetAllocProperties;

    dditable.pfnGetAddressRange                          = pDdiTable->pfnGetAddressRange;
    pDdiTable->pfnGetAddressRange                        = validation_layer::zeMemGetAddressRange;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = validation_layer::zeMemGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeMemOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeMemCloseIpcHandle;

    dditable.pfnFreeExt                                  = pDdiTable->pfnFreeExt;
    pDdiTable->pfnFreeExt                                = validation_layer::zeMemFreeExt;

    dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
    pDdiTable->pfnPutIpcHandle                           = validation_layer::zeMemPutIpcHandle;

    dditable.pfnGetPitchFor2dImage                       = pDdiTable->pfnGetPitchFor2dImage;
    pDdiTable->pfnGetPitchFor2dImage                     = validation_layer::zeMemGetPitchFor2dImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MemExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_exp_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.MemExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetIpcHandleFromFileDescriptorExp        = pDdiTable->pfnGetIpcHandleFromFileDescriptorExp;
    pDdiTable->pfnGetIpcHandleFromFileDescriptorExp      = validation_layer::zeMemGetIpcHandleFromFileDescriptorExp;

    dditable.pfnGetFileDescriptorFromIpcHandleExp        = pDdiTable->pfnGetFileDescriptorFromIpcHandleExp;
    pDdiTable->pfnGetFileDescriptorFromIpcHandleExp      = validation_layer::zeMemGetFileDescriptorFromIpcHandleExp;

    dditable.pfnSetAtomicAccessAttributeExp              = pDdiTable->pfnSetAtomicAccessAttributeExp;
    pDdiTable->pfnSetAtomicAccessAttributeExp            = validation_layer::zeMemSetAtomicAccessAttributeExp;

    dditable.pfnGetAtomicAccessAttributeExp              = pDdiTable->pfnGetAtomicAccessAttributeExp;
    pDdiTable->pfnGetAtomicAccessAttributeExp            = validation_layer::zeMemGetAtomicAccessAttributeExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeModuleCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeModuleDestroy;

    dditable.pfnDynamicLink                              = pDdiTable->pfnDynamicLink;
    pDdiTable->pfnDynamicLink                            = validation_layer::zeModuleDynamicLink;

    dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
    pDdiTable->pfnGetNativeBinary                        = validation_layer::zeModuleGetNativeBinary;

    dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
    pDdiTable->pfnGetGlobalPointer                       = validation_layer::zeModuleGetGlobalPointer;

    dditable.pfnGetKernelNames                           = pDdiTable->pfnGetKernelNames;
    pDdiTable->pfnGetKernelNames                         = validation_layer::zeModuleGetKernelNames;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeModuleGetProperties;

    dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
    pDdiTable->pfnGetFunctionPointer                     = validation_layer::zeModuleGetFunctionPointer;

    dditable.pfnInspectLinkageExt                        = pDdiTable->pfnInspectLinkageExt;
    pDdiTable->pfnInspectLinkageExt                      = validation_layer::zeModuleInspectLinkageExt;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.ModuleBuildLog;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeModuleBuildLogDestroy;

    dditable.pfnGetString                                = pDdiTable->pfnGetString;
    pDdiTable->pfnGetString                              = validation_layer::zeModuleBuildLogGetString;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PhysicalMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_physical_mem_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.PhysicalMem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zePhysicalMemCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zePhysicalMemDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Sampler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeSamplerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeSamplerDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VirtualMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_virtual_mem_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.VirtualMem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnReserve                                  = pDdiTable->pfnReserve;
    pDdiTable->pfnReserve                                = validation_layer::zeVirtualMemReserve;

    dditable.pfnFree                                     = pDdiTable->pfnFree;
    pDdiTable->pfnFree                                   = validation_layer::zeVirtualMemFree;

    dditable.pfnQueryPageSize                            = pDdiTable->pfnQueryPageSize;
    pDdiTable->pfnQueryPageSize                          = validation_layer::zeVirtualMemQueryPageSize;

    dditable.pfnMap                                      = pDdiTable->pfnMap;
    pDdiTable->pfnMap                                    = validation_layer::zeVirtualMemMap;

    dditable.pfnUnmap                                    = pDdiTable->pfnUnmap;
    pDdiTable->pfnUnmap                                  = validation_layer::zeVirtualMemUnmap;

    dditable.pfnSetAccessAttribute                       = pDdiTable->pfnSetAccessAttribute;
    pDdiTable->pfnSetAccessAttribute                     = validation_layer::zeVirtualMemSetAccessAttribute;

    dditable.pfnGetAccessAttribute                       = pDdiTable->pfnGetAccessAttribute;
    pDdiTable->pfnGetAccessAttribute                     = validation_layer::zeVirtualMemGetAccessAttribute;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricEdgeExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricEdgeExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_edge_exp_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.FabricEdgeExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
    pDdiTable->pfnGetExp                                 = validation_layer::zeFabricEdgeGetExp;

    dditable.pfnGetVerticesExp                           = pDdiTable->pfnGetVerticesExp;
    pDdiTable->pfnGetVerticesExp                         = validation_layer::zeFabricEdgeGetVerticesExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricEdgeGetPropertiesExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricVertexExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricVertexExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_vertex_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.FabricVertexExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
    pDdiTable->pfnGetExp                                 = validation_layer::zeFabricVertexGetExp;

    dditable.pfnGetSubVerticesExp                        = pDdiTable->pfnGetSubVerticesExp;
    pDdiTable->pfnGetSubVerticesExp                      = validation_layer::zeFabricVertexGetSubVerticesExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricVertexGetPropertiesExp;

    dditable.pfnGetDeviceExp                             = pDdiTable->pfnGetDeviceExp;
    pDdiTable->pfnGetDeviceExp                           = validation_layer::zeFabricVertexGetDeviceExp;

    return result;
}

#if defined(__cplusplus)
};
#endif
