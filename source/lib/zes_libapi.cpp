/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libapi.cpp
 *
 * @brief C++ static library for zes
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize 'oneAPI' System Resource Management (sysman)
/// 
/// @details
///     - The application must call this function or ::zeInit with the
///       ::ZES_ENABLE_SYSMAN environment variable set before calling any other
///       sysman function.
///     - If this function is not called then all other sysman functions will
///       return ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - This function will only initialize sysman. To initialize other
///       functions, call ::zeInit.
///     - There is no requirement to call this function before or after
///       ::zeInit.
///     - Only one instance of sysman will be initialized per process.
///     - The application must call this function after forking new processes.
///       Each forked process must call this function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe for scenarios
///       where multiple libraries may initialize sysman simultaneously.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0x1 < flags`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t ZE_APICALL
zesInit(
    zes_init_flags_t flags                          ///< [in] initialization flags.
                                                    ///< currently unused, must be 0 (default).
    )
{
    static ze_result_t result = ZE_RESULT_SUCCESS;
    std::call_once(ze_lib::context->initOnceSysMan, [flags]() {
        result = ze_lib::context->Init(flags, true, nullptr);

    });

    if( ZE_RESULT_SUCCESS != result )
        return result;

    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnInit = ze_lib::context->zesDdiTable.load()->Global.pfnInit;
    if( nullptr == pfnInit ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sysman driver instances
/// 
/// @details
///     - A sysman driver represents a collection of physical devices.
///     - Multiple calls to this function will return identical sysman driver
///       handles, in the same order.
///     - The application may pass nullptr for pDrivers when only querying the
///       number of sysman drivers.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDriverGet(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman driver instances.
                                                    ///< if count is zero, then the loader shall update the value with the
                                                    ///< total number of sysman drivers available.
                                                    ///< if count is greater than the number of sysman drivers available, then
                                                    ///< the loader shall update the value with the correct number of sysman
                                                    ///< drivers available.
    zes_driver_handle_t* phDrivers                  ///< [in,out][optional][range(0, *pCount)] array of sysman driver instance handles.
                                                    ///< if count is less than the number of sysman drivers available, then the
                                                    ///< loader shall only retrieve that number of sysman drivers.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if (ze_lib::context->zesDdiTable == nullptr) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zesDdiTable.load()->Driver.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    ze_lib::context->zesInuse = true;

    return pfnGet( pCount, phDrivers );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves extension properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDriverGetExtensionProperties(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of extension properties available.
                                                    ///< if count is greater than the number of extension properties available,
                                                    ///< then the driver shall update the value with the correct number of
                                                    ///< extension properties available.
    zes_driver_extension_properties_t* pExtensionProperties ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< extension properties.
                                                    ///< if count is less than the number of extension properties available,
                                                    ///< then driver shall only retrieve that number of extension properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionProperties = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionProperties;
    if( nullptr == pfnGetExtensionProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves function pointer for vendor-specific or experimental
///        extensions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == name`
///         + `nullptr == ppFunctionAddress`
ze_result_t ZE_APICALL
zesDriverGetExtensionFunctionAddress(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
    const char* name,                               ///< [in] extension function name
    void** ppFunctionAddress                        ///< [out] pointer to function pointer
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetExtensionFunctionAddress = ze_lib::context->zesDdiTable.load()->Driver.pfnGetExtensionFunctionAddress;
    if( nullptr == pfnGetExtensionFunctionAddress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sysman devices within a sysman driver
/// 
/// @details
///     - Multiple calls to this function will return identical sysman device
///       handles, in the same order.
///     - The number and order of handles returned from this function is NOT
///       affected by the ::ZE_AFFINITY_MASK, ::ZE_ENABLE_PCI_ID_DEVICE_ORDER,
///       or ::ZE_FLAT_DEVICE_HIERARCHY environment variables.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceGet(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sysman devices available.
                                                    ///< if count is greater than the number of sysman devices available, then
                                                    ///< the driver shall update the value with the correct number of sysman
                                                    ///< devices available.
    zes_device_handle_t* phDevices                  ///< [in,out][optional][range(0, *pCount)] array of handle of sysman devices.
                                                    ///< if count is less than the number of sysman devices available, then
                                                    ///< driver shall only retrieve that number of sysman devices.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGet = ze_lib::context->zesDdiTable.load()->Device.pfnGet;
    if( nullptr == pfnGet ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGet( hDriver, pCount, phDevices );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDeviceGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDevice, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about the state of the device - if a reset is
///        required, reasons for the reset and if the device has been repaired
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDeviceGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Device.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hDevice, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - All applications using the device should be stopped before calling
///       this function.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or an
///       implementation defined timeout occurred waiting for the reset to
///       complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Reset cannot be performed because applications are using this device.
///     - ::ZE_RESULT_ERROR_UNKNOWN
///         + There were problems unloading the device driver, performing a bus reset or reloading the device driver.
ze_result_t ZE_APICALL
zesDeviceReset(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                    ///< device will be forcibly killed.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReset = ze_lib::context->zesDdiTable.load()->Device.pfnReset;
    if( nullptr == pfnReset ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReset( hDevice, force );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset device extension
/// 
/// @details
///     - Performs a PCI bus reset of the device. This will result in all
///       current device state being lost.
///     - Prior to calling this function, user is responsible for closing
///       applications using the device unless force argument is specified.
///     - If the force argument is specified, all applications using the device
///       will be forcibly killed.
///     - The function will block until the device has restarted or a
///       implementation specific timeout occurred waiting for the reset to
///       complete.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
///         + Reset cannot be performed because applications are using this device.
///     - ::ZE_RESULT_ERROR_UNKNOWN
///         + There were problems unloading the device driver, performing a bus reset or reloading the device driver.
ze_result_t ZE_APICALL
zesDeviceResetExt(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResetExt = ze_lib::context->zesDdiTable.load()->Device.pfnResetExt;
    if( nullptr == pfnResetExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResetExt( hDevice, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about host processes using the device
/// 
/// @details
///     - The number of processes connected to the device is dynamic. This means
///       that between a call to determine the value of pCount and the
///       subsequent call, the number of processes may have increased or
///       decreased. It is recommended that a large array be passed in so as to
///       avoid receiving the error ::ZE_RESULT_ERROR_INVALID_SIZE. Also, always
///       check the returned value in pCount since it may be less than the
///       earlier call to get the required array size.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INVALID_SIZE
///         + The provided value of pCount is not big enough to store information about all the processes currently attached to the device.
ze_result_t ZE_APICALL
zesDeviceProcessesGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of processes currently attached to the device.
                                                    ///< if count is greater than the number of processes currently attached to
                                                    ///< the device, then the driver shall update the value with the correct
                                                    ///< number of processes.
    zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information.
                                                    ///< if count is less than the number of processes currently attached to
                                                    ///< the device, then the driver shall only retrieve information about that
                                                    ///< number of processes. In this case, the return code will ::ZE_RESULT_ERROR_INVALID_SIZE.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnProcessesGetState = ze_lib::context->zesDdiTable.load()->Device.pfnProcessesGetState;
    if( nullptr == pfnProcessesGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnProcessesGetState( hDevice, pCount, pProcesses );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI properties - address, max speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDevicePciGetProperties(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetProperties = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetProperties;
    if( nullptr == pfnPciGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetProperties( hDevice, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current PCI state - current speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDevicePciGetState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetState = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetState;
    if( nullptr == pfnPciGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetState( hDevice, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get information about each configured bar
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDevicePciGetBars(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of PCI bars that are setup.
                                                    ///< if count is greater than the number of PCI bars that are setup, then
                                                    ///< the driver shall update the value with the correct number of PCI bars.
    zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of information about setup
                                                    ///< PCI bars.
                                                    ///< if count is less than the number of PCI bars that are setup, then the
                                                    ///< driver shall only retrieve information about that number of PCI bars.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetBars = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetBars;
    if( nullptr == pfnPciGetBars ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetBars( hDevice, pCount, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get PCI stats - bandwidth, number of packets, number of replays
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesDevicePciGetStats(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnPciGetStats = ze_lib::context->zesDdiTable.load()->Device.pfnPciGetStats;
    if( nullptr == pfnPciGetStats ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnPciGetStats( hDevice, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the overclock waiver.The overclock waiver setting is persistent
///        until the next pcode boot
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This product does not support overclocking
ze_result_t ZE_APICALL
zesDeviceSetOverclockWaiver(
    zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetOverclockWaiver = ze_lib::context->zesDdiTable.load()->Device.pfnSetOverclockWaiver;
    if( nullptr == pfnSetOverclockWaiver ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetOverclockWaiver( hDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the list of supported overclock domains for this device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOverclockDomains`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceGetOverclockDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                    ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                    ///< doesn't support overclocking.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockDomains;
    if( nullptr == pfnGetOverclockDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOverclockDomains( hDevice, pOverclockDomains );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the list of supported overclock controls available for one of the
///        supported overclock domains on the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_DOMAIN_ADM < domainType`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pAvailableControls`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceGetOverclockControls(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_overclock_domain_t domainType,              ///< [in] Domain type.
    uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                    ///< specified overclock domain (a bit for each of enum
                                                    ///< ::zes_overclock_control_t).
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetOverclockControls = ze_lib::context->zesDdiTable.load()->Device.pfnGetOverclockControls;
    if( nullptr == pfnGetOverclockControls ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Reset all overclock settings to default values (shipped = 1 or
///        manufacturing =0)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceResetOverclockSettings(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                    ///< manufacturing state
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnResetOverclockSettings = ze_lib::context->zesDdiTable.load()->Device.pfnResetOverclockSettings;
    if( nullptr == pfnResetOverclockSettings ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnResetOverclockSettings( hDevice, onShippedState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Determine the state of overclocking
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOverclockMode`
///         + `nullptr == pWaiverSetting`
///         + `nullptr == pOverclockState`
///         + `nullptr == pPendingAction`
///         + `nullptr == pPendingReset`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesDeviceReadOverclockState(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
    ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
    ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
    zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                    ///< overclock control or reset overclock settings.
    ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnReadOverclockState = ze_lib::context->zesDdiTable.load()->Device.pfnReadOverclockState;
    if( nullptr == pfnReadOverclockState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of overclock domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumOverclockDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_overclock_handle_t* phDomainHandle          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumOverclockDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumOverclockDomains;
    if( nullptr == pfnEnumOverclockDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get overclock domain control properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDomainProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainProperties;
    if( nullptr == pfnGetDomainProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainProperties( hDomainHandle, pDomainProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read overclock VF min,max and step values
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pVFProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainVFProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainVFProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainVFProperties;
    if( nullptr == pfnGetDomainVFProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read overclock control values - min/max/step/default/ref
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pControlProperties`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetDomainControlProperties(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
    zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDomainControlProperties = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetDomainControlProperties;
    if( nullptr == pfnGetDomainControlProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the current value for a given overclock control
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlCurrentValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
    zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
    double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlCurrentValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlCurrentValue;
    if( nullptr == pfnGetControlCurrentValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the the reset pending value for a given overclock control
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlPendingValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
    double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                    ///< format of the value depend on the control type.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlPendingValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlPendingValue;
    if( nullptr == pfnGetControlPendingValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the value for a given overclock control
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pPendingAction`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockSetControlUserValue(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
    double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                    ///< depend on the control type.
    zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetControlUserValue = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetControlUserValue;
    if( nullptr == pfnSetControlUserValue ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Determine the state of an overclock control
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pControlState`
///         + `nullptr == pPendingAction`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetControlState(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
    zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
    zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetControlState = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetControlState;
    if( nullptr == pfnGetControlState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Read the frequency or voltage of a V-F point from the default or
///        custom V-F curve.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_VF_TYPE_FREQ < VFType`
///         + `::ZES_VF_ARRAY_TYPE_LIVE_VF_ARRAY < VFArrayType`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == PointValue`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockGetVFPointValues(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
    zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
    uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
    uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                    ///< units from the custom V-F curve at the specified zero-based index 
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnGetVFPointValues;
    if( nullptr == pfnGetVFPointValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Write the frequency or voltage of a V-F point to custom V-F curve.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDomainHandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_VF_TYPE_FREQ < VFType`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this control domain
ze_result_t ZE_APICALL
zesOverclockSetVFPointValues(
    zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
    zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
    uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
    uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                    ///< custom V-F curve at the specified zero-based index 
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFPointValues = ze_lib::context->zesDdiTable.load()->Overclock.pfnSetVFPointValues;
    if( nullptr == pfnSetVFPointValues ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of diagnostics test suites
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumDiagnosticTestSuites(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumDiagnosticTestSuites = ze_lib::context->zesDdiTable.load()->Device.pfnEnumDiagnosticTestSuites;
    if( nullptr == pfnEnumDiagnosticTestSuites ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties of a diagnostics test suite
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesDiagnosticsGetProperties(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                    ///< suite
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hDiagnostics, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get individual tests that can be run separately. Not all test suites
///        permit running individual tests, check the `haveTests` member of
///        ::zes_diag_properties_t.
/// 
/// @details
///     - The list of available tests is returned in order of increasing test
///       index (see the `index` member of ::zes_diag_test_t).
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDiagnosticsGetTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of tests that are available.
                                                    ///< if count is greater than the number of tests that are available, then
                                                    ///< the driver shall update the value with the correct number of tests.
    zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] array of information about
                                                    ///< individual tests sorted by increasing value of the `index` member of ::zes_diag_test_t.
                                                    ///< if count is less than the number of tests that are available, then the
                                                    ///< driver shall only retrieve that number of tests.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnGetTests;
    if( nullptr == pfnGetTests ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTests( hDiagnostics, pCount, pTests );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Run a diagnostics test suite, either all tests or a subset of tests.
/// 
/// @details
///     - WARNING: Running diagnostics may destroy current device state
///       information. Gracefully close any running workloads before initiating.
///     - To run all tests in a test suite, set start =
///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
///     - If the test suite permits running individual tests, the `haveTests`
///       member of ::zes_diag_properties_t will be true. In this case, the
///       function ::zesDiagnosticsGetTests() can be called to get the list of
///       tests and corresponding indices that can be supplied to the arguments
///       start and end in this function.
///     - This function will block until the diagnostics have completed and
///       force reset based on result
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDiagnostics`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pResult`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform diagnostics.
ze_result_t ZE_APICALL
zesDiagnosticsRunTests(
    zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
    uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                    ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
    uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                    ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
    zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnRunTests = ze_lib::context->zesDdiTable.load()->Diagnostics.pfnRunTests;
    if( nullptr == pfnRunTests ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Is ECC functionality available - true or false?
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pAvailable`
ze_result_t ZE_APICALL
zesDeviceEccAvailable(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEccAvailable = ze_lib::context->zesDdiTable.load()->Device.pfnEccAvailable;
    if( nullptr == pfnEccAvailable ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEccAvailable( hDevice, pAvailable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Is ECC support configurable - true or false?
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfigurable`
ze_result_t ZE_APICALL
zesDeviceEccConfigurable(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEccConfigurable = ze_lib::context->zesDdiTable.load()->Device.pfnEccConfigurable;
    if( nullptr == pfnEccConfigurable ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEccConfigurable( hDevice, pConfigurable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current ECC state, pending state, and pending action
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesDeviceGetEccState(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnGetEccState;
    if( nullptr == pfnGetEccState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEccState( hDevice, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set new ECC state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - ::zesDeviceGetState should be called to determine pending action
///       required to implement state change.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == newState`
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_DEVICE_ECC_STATE_DISABLED < newState->state`
///     - ::ZE_RESULT_WARNING_ACTION_REQUIRED
///         + User must look at the pendingAction attribute of pState & perform the action required to complete the ECC state change.
ze_result_t ZE_APICALL
zesDeviceSetEccState(
    zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
    const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
    zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEccState = ze_lib::context->zesDdiTable.load()->Device.pfnSetEccState;
    if( nullptr == pfnSetEccState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEccState( hDevice, newState, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of engine groups
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumEngineGroups(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumEngineGroups = ze_lib::context->zesDdiTable.load()->Device.pfnEnumEngineGroups;
    if( nullptr == pfnEnumEngineGroups ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumEngineGroups( hDevice, pCount, phEngine );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine group properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesEngineGetProperties(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Engine.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hEngine, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the activity stats for an engine group.
/// 
/// @details
///     - This function also returns the engine activity inside a Virtual
///       Machine (VM), in the presence of hardware virtualization (SRIOV)
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pStats`
ze_result_t ZE_APICALL
zesEngineGetActivity(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                    ///< counters.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetActivity = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivity;
    if( nullptr == pfnGetActivity ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetActivity( hEngine, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Specify the list of events to listen to for a given device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xffff < events`
ze_result_t ZE_APICALL
zesDeviceEventRegister(
    zes_device_handle_t hDevice,                    ///< [in] The device handle.
    zes_event_type_flags_t events                   ///< [in] List of events to listen to.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventRegister = ze_lib::context->zesDdiTable.load()->Device.pfnEventRegister;
    if( nullptr == pfnEventRegister ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventRegister( hDevice, events );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListen(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if `UINT32_MAX`, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventListen = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListen;
    if( nullptr == pfnEventListen ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Wait for events to be received from a one or more devices.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevices`
///         + `nullptr == pNumDeviceEvents`
///         + `nullptr == pEvents`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to listen to events.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or more of the supplied device handles belongs to a different driver.
ze_result_t ZE_APICALL
zesDriverEventListenEx(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                    ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                    ///< if zero, then will check status and return immediately;
                                                    ///< if `UINT64_MAX`, then function will not return until events arrive.
    uint32_t count,                                 ///< [in] Number of device handles in phDevices.
    zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                    ///< devices from the provided driver handle can be specified in this list.
    uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                    ///< generated events. If non-zero, check pEvents to determine the devices
                                                    ///< and events that were received.
    zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                    ///< device listened in phDevices.
                                                    ///< This array must be at least as big as count.
                                                    ///< For every device handle in phDevices, this will provide the events
                                                    ///< that occurred for that device at the same position in this array. If
                                                    ///< no event was received for a given device, the corresponding array
                                                    ///< entry will be zero.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEventListenEx = ze_lib::context->zesDdiTable.load()->Driver.pfnEventListenEx;
    if( nullptr == pfnEventListenEx ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of Fabric ports in a device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFabricPorts(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFabricPorts = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFabricPorts;
    if( nullptr == pfnEnumFabricPorts ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFabricPorts( hDevice, pCount, phPort );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFabricPortGetProperties(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPort, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port link type
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLinkType`
ze_result_t ZE_APICALL
zesFabricPortGetLinkType(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                    ///< port.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLinkType = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetLinkType;
    if( nullptr == pfnGetLinkType ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLinkType( hPort, pLinkType );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFabricPortGetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set Fabric port configuration
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFabricPortSetConfig(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->FabricPort.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hPort, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port state - status (health/degraded/failed/disabled),
///        reasons for link degradation or instability, current rx/tx speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFabricPortGetState(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hPort, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThroughput`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesFabricPortGetThroughput(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetThroughput;
    if( nullptr == pfnGetThroughput ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThroughput( hPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric Port Error Counters
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - The memory backing the arrays for phPorts and ppThroughputs must be
///       allocated in system memory by the user who is also responsible for
///       releasing them when they are no longer needed.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPort`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pErrors`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesFabricPortGetFabricErrorCounters(
    zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
    zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFabricErrorCounters = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetFabricErrorCounters;
    if( nullptr == pfnGetFabricErrorCounters ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFabricErrorCounters( hPort, pErrors );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Fabric port throughput from multiple ports in a single call
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phPort`
///         + `nullptr == pThroughput`
ze_result_t ZE_APICALL
zesFabricPortGetMultiPortThroughput(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
    zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                    ///< to gather throughput values. 
    zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                    ///< from multiple ports of type ::zes_fabric_port_throughput_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMultiPortThroughput = ze_lib::context->zesDdiTable.load()->FabricPort.pfnGetMultiPortThroughput;
    if( nullptr == pfnGetMultiPortThroughput ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of fans
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFans(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFans = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFans;
    if( nullptr == pfnEnumFans ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFans( hDevice, pCount, phFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFanGetProperties(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Fan.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFan, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get fan configurations and the current fan speed mode (default, fixed,
///        temp-speed table)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesFanGetConfig(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Fan.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hFan, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to run with hardware factory settings (set mode to
///        ::ZES_FAN_SPEED_MODE_DEFAULT)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFanSetDefaultMode(
    zes_fan_handle_t hFan                           ///< [in] Handle for the component.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetDefaultMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetDefaultMode;
    if( nullptr == pfnSetDefaultMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetDefaultMode( hFan );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to rotate at a fixed speed (set mode to
///        ::ZES_FAN_SPEED_MODE_FIXED)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fixing the fan speed not supported by the hardware or the fan speed units are not supported. See the `supportedModes` and `supportedUnits` members of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanSetFixedSpeedMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetFixedSpeedMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetFixedSpeedMode;
    if( nullptr == pfnSetFixedSpeedMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetFixedSpeedMode( hFan, speed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure the fan to adjust speed based on a temperature/speed table
///        (set mode to ::ZES_FAN_SPEED_MODE_TABLE)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == speedTable`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The temperature/speed pairs in the array are not sorted on temperature from lowest to highest.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Fan speed table not supported by the hardware or the fan speed units are not supported. See the `supportedModes` and `supportedUnits` members of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanSetSpeedTableMode(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetSpeedTableMode = ze_lib::context->zesDdiTable.load()->Fan.pfnSetSpeedTableMode;
    if( nullptr == pfnSetSpeedTableMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetSpeedTableMode( hFan, speedTable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a fan - current mode and speed
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFan`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_FAN_SPEED_UNITS_PERCENT < units`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSpeed`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The requested fan speed units are not supported. See the `supportedUnits` member of ::zes_fan_properties_t.
ze_result_t ZE_APICALL
zesFanGetState(
    zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
    zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
    int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                    ///< requested. A value of -1 indicates that the fan speed cannot be
                                                    ///< measured.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Fan.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hFan, units, pSpeed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of firmwares
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFirmwares(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFirmwares = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFirmwares;
    if( nullptr == pfnEnumFirmwares ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFirmwares( hDevice, pCount, phFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get firmware properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFirmwareGetProperties(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                    ///< firmware
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFirmware, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Flash a new firmware image
/// 
/// @details
///     - Any running workload must be gracefully closed before invoking this
///       function.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This is a non-blocking call. Application may call
///       ::zesFirmwareGetFlashProgress to get completion status.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImage`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to perform this operation.
ze_result_t ZE_APICALL
zesFirmwareFlash(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    void* pImage,                                   ///< [in] Image of the new firmware to flash.
    uint32_t size                                   ///< [in] Size of the flash image.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnFlash = ze_lib::context->zesDdiTable.load()->Firmware.pfnFlash;
    if( nullptr == pfnFlash ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnFlash( hFirmware, pImage, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Firmware Flash Progress
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCompletionPercent`
ze_result_t ZE_APICALL
zesFirmwareGetFlashProgress(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetFlashProgress = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetFlashProgress;
    if( nullptr == pfnGetFlashProgress ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetFlashProgress( hFirmware, pCompletionPercent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get Firmware Console Logs
/// 
/// @details
///     - The caller may pass nullptr for pFirmwareLog and set pSize to zero
///       when querying only for size.
///     - The caller must provide memory for Firmware log.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pSize`
ze_result_t ZE_APICALL
zesFirmwareGetConsoleLogs(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    size_t* pSize,                                  ///< [in,out] size of firmware log
    char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConsoleLogs = ze_lib::context->zesDdiTable.load()->Firmware.pfnGetConsoleLogs;
    if( nullptr == pfnGetConsoleLogs ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of frequency domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumFrequencyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumFrequencyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumFrequencyDomains;
    if( nullptr == pfnEnumFrequencyDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency properties - available frequencies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesFrequencyGetProperties(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hFrequency, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get available non-overclocked hardware clock frequencies for the
///        frequency domain
/// 
/// @details
///     - The list of available frequencies is returned in order of slowest to
///       fastest.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesFrequencyGetAvailableClocks(
    zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of frequencies that are available.
                                                    ///< if count is greater than the number of frequencies that are available,
                                                    ///< then the driver shall update the value with the correct number of frequencies.
    double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                    ///< MHz and sorted from slowest to fastest.
                                                    ///< if count is less than the number of frequencies that are available,
                                                    ///< then the driver shall only retrieve that number of frequencies.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetAvailableClocks = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetAvailableClocks;
    if( nullptr == pfnGetAvailableClocks ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
ze_result_t ZE_APICALL
zesFrequencyGetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetRange;
    if( nullptr == pfnGetRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set frequency range between which the hardware can operate.
/// 
/// @details
///     - The application may call this function with the frequency range min
///       and max values set to `-1` to request the frequency be (re)set to the
///       default values.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pLimits`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencySetRange(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                    ///< specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetRange = ze_lib::context->zesDdiTable.load()->Frequency.pfnSetRange;
    if( nullptr == pfnSetRange ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetRange( hFrequency, pLimits );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current frequency state - frequency request, actual frequency, TDP
///        limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesFrequencyGetState(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hFrequency, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get frequency throttle time
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThrottleTime`
ze_result_t ZE_APICALL
zesFrequencyGetThrottleTime(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                    ///< specified domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetThrottleTime = ze_lib::context->zesDdiTable.load()->Frequency.pfnGetThrottleTime;
    if( nullptr == pfnGetThrottleTime ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetThrottleTime( hFrequency, pThrottleTime );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the overclocking capabilities.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcCapabilities`
ze_result_t ZE_APICALL
zesFrequencyOcGetCapabilities(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetCapabilities = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetCapabilities;
    if( nullptr == pfnOcGetCapabilities ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking frequency target, if extended moded is
///        supported, will returned in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                    ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than the `maxOcFrequency` member of
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetFrequencyTarget;
    if( nullptr == pfnOcGetFrequencyTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking frequency target, if extended moded is
///        supported, can be set in 1 Mhz granularity.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetFrequencyTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                    ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                    ///< cannot be greater than the `maxOcFrequency` member of
                                                    ///< ::zes_oc_capabilities_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetFrequencyTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetFrequencyTarget;
    if( nullptr == pfnOcSetFrequencyTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentVoltageTarget`
///         + `nullptr == pCurrentVoltageOffset`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                    ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
    double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                    ///< Valid range is between the `minOcVoltageOffset` and
                                                    ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetVoltageTarget;
    if( nullptr == pfnOcGetVoltageTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking voltage settings.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetVoltageTarget(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                    ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
    double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                    ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                    ///< Valid range is between the `minOcVoltageOffset` and
                                                    ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetVoltageTarget = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetVoltageTarget;
    if( nullptr == pfnOcSetVoltageTarget ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_OC_MODE_FIXED < CurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetMode;
    if( nullptr == pfnOcSetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetMode( hFrequency, CurrentOcMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current overclocking mode.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCurrentOcMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The specified voltage and/or frequency overclock settings exceed the hardware values (see the `maxOcFrequency`, `maxOcVoltage`, `minOcVoltageOffset` and `maxOcVoltageOffset` members of ::zes_oc_capabilities_t).
///         + Requested voltage overclock is very high but the `isHighVoltModeEnabled` member of ::zes_oc_capabilities_t is not enabled for the device.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcGetMode(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetMode = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetMode;
    if( nullptr == pfnOcGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetMode( hFrequency, pCurrentOcMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum current limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcIccMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + Capability the `isIccMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
ze_result_t ZE_APICALL
zesFrequencyOcGetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                    ///< successful return.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetIccMax;
    if( nullptr == pfnOcGetIccMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetIccMax( hFrequency, pOcIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum current limit setting.
/// 
/// @details
///     - Setting ocIccMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The `isIccMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified current limit is too low or too high.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetIccMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetIccMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetIccMax;
    if( nullptr == pfnOcSetIccMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetIccMax( hFrequency, ocIccMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the maximum temperature limit setting.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pOcTjMax`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
ze_result_t ZE_APICALL
zesFrequencyOcGetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                    ///< on successful return.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcGetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcGetTjMax;
    if( nullptr == pfnOcGetTjMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcGetTjMax( hFrequency, pOcTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the maximum temperature limit setting.
/// 
/// @details
///     - Setting ocTjMax to 0.0 will return the value to the factory default.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFrequency`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Overclocking is not supported on this frequency domain (see the `isOcSupported` member of ::zes_oc_capabilities_t).
///         + The `isTjMaxSupported` member of ::zes_oc_capabilities_t is false for this frequency domain.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Overclocking feature is locked on this frequency domain.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + The specified temperature limit is too high.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesFrequencyOcSetTjMax(
    zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
    double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnOcSetTjMax = ze_lib::context->zesDdiTable.load()->Frequency.pfnOcSetTjMax;
    if( nullptr == pfnOcSetTjMax ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnOcSetTjMax( hFrequency, ocTjMax );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of LEDs
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumLeds(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumLeds = ze_lib::context->zesDdiTable.load()->Device.pfnEnumLeds;
    if( nullptr == pfnEnumLeds ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumLeds( hDevice, pCount, phLed );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get LED properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesLedGetProperties(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Led.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hLed, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current state of a LED - on/off, color
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesLedGetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Led.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hLed, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Turn the LED on/off
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesLedSetState(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetState = ze_lib::context->zesDdiTable.load()->Led.pfnSetState;
    if( nullptr == pfnSetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetState( hLed, enable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the color of the LED
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hLed`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pColor`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This LED doesn't not support color changes. See the `haveRGB` member of ::zes_led_properties_t.
ze_result_t ZE_APICALL
zesLedSetColor(
    zes_led_handle_t hLed,                          ///< [in] Handle for the component.
    const zes_led_color_t* pColor                   ///< [in] New color of the LED.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetColor = ze_lib::context->zesDdiTable.load()->Led.pfnSetColor;
    if( nullptr == pfnSetColor ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetColor( hLed, pColor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of memory modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumMemoryModules(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumMemoryModules = ze_lib::context->zesDdiTable.load()->Device.pfnEnumMemoryModules;
    if( nullptr == pfnEnumMemoryModules ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumMemoryModules( hDevice, pCount, phMemory );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesMemoryGetProperties(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Memory.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hMemory, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory state - health, allocated
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesMemoryGetState(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Memory.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hMemory, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory bandwidth
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hMemory`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pBandwidth`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to query this telemetry.
ze_result_t ZE_APICALL
zesMemoryGetBandwidth(
    zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
    zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                    ///< to memory, as well as the current maximum bandwidth.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetBandwidth = ze_lib::context->zesDdiTable.load()->Memory.pfnGetBandwidth;
    if( nullptr == pfnGetBandwidth ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetBandwidth( hMemory, pBandwidth );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handles to accelerator domains whose performance can be optimized
///        via a Performance Factor
/// 
/// @details
///     - A Performance Factor should be tuned for each workload.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPerformanceFactorDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPerformanceFactorDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPerformanceFactorDomains;
    if( nullptr == pfnEnumPerformanceFactorDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties about a Performance Factor domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPerformanceFactorGetProperties(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                    ///< Factor domain.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPerf, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current Performance Factor for a given domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pFactor`
ze_result_t ZE_APICALL
zesPerformanceFactorGetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                    ///< hardware (may not be the same as the requested Performance Factor).
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hPerf, pFactor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change the performance factor for a domain
/// 
/// @details
///     - The Performance Factor is a number between 0 and 100.
///     - A Performance Factor is a hint to the hardware. Depending on the
///       hardware, the request may not be granted. Follow up this function with
///       a call to ::zesPerformanceFactorGetConfig() to determine the actual
///       factor being used by the hardware.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPerf`
ze_result_t ZE_APICALL
zesPerformanceFactorSetConfig(
    zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
    double factor                                   ///< [in] The new Performance Factor.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->PerformanceFactor.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hPerf, factor );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power domains
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPowerDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPowerDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPowerDomains;
    if( nullptr == pfnEnumPowerDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPowerDomains( hDevice, pCount, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of the PCIe card-level power
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + The device does not provide access to card level power controls or telemetry. An invalid power domain handle will be returned in phPower.
ze_result_t ZE_APICALL
zesDeviceGetCardPowerDomain(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCardPowerDomain = ze_lib::context->zesDdiTable.load()->Device.pfnGetCardPowerDomain;
    if( nullptr == pfnGetCardPowerDomain ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCardPowerDomain( hDevice, phPower );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a power domain
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPowerGetProperties(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Power.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPower, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy counter
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pEnergy`
ze_result_t ZE_APICALL
zesPowerGetEnergyCounter(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                    ///< timestamp when the last counter value was measured.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEnergyCounter = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyCounter;
    if( nullptr == pfnGetEnergyCounter ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEnergyCounter( hPower, pEnergy );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] Use ::zesPowerGetLimitsExt.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
ze_result_t ZE_APICALL
zesPowerGetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                    ///< current sustained power limits will not be returned.
    zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                    ///< peak power limits will not be returned.
    zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                    ///< power limits will not be returned.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimits;
    if( nullptr == pfnGetLimits ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] Use ::zesPowerSetLimitsExt.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t ZE_APICALL
zesPowerSetLimits(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                    ///< will be made to the sustained power limits.
    const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                    ///< be made to the burst power limits.
    const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                    ///< be made to the peak power limits.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetLimits = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimits;
    if( nullptr == pfnSetLimits ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get energy threshold
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pThreshold`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check the `isEnergyThresholdSupported` member of ::zes_power_properties_t).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesPowerGetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                    ///< enabled/energy threshold/process ID.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnGetEnergyThreshold;
    if( nullptr == pfnGetEnergyThreshold ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetEnergyThreshold( hPower, pThreshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set energy threshold
/// 
/// @details
///     - An event ::ZES_EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED will be
///       generated when the delta energy consumed starting from this call
///       exceeds the specified threshold. Use the function
///       ::zesDeviceEventRegister() to start receiving the event.
///     - Only one running process can control the energy threshold at a given
///       time. If another process attempts to change the energy threshold, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesPowerGetEnergyThreshold() to determine the process ID currently
///       controlling this setting.
///     - Calling this function will remove any pending energy thresholds and
///       start counting from the time of this call.
///     - Once the energy threshold has been reached and the event generated,
///       the threshold is automatically removed. It is up to the application to
///       request a new threshold.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Energy threshold not supported on this power domain (check the `isEnergyThresholdSupported` member of ::zes_power_properties_t).
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process has set the energy threshold.
ze_result_t ZE_APICALL
zesPowerSetEnergyThreshold(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    double threshold                                ///< [in] The energy threshold to be set in joules.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetEnergyThreshold = ze_lib::context->zesDdiTable.load()->Power.pfnSetEnergyThreshold;
    if( nullptr == pfnSetEnergyThreshold ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetEnergyThreshold( hPower, threshold );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of power supplies
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumPsus(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumPsus = ze_lib::context->zesDdiTable.load()->Device.pfnEnumPsus;
    if( nullptr == pfnEnumPsus ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumPsus( hDevice, pCount, phPsu );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power supply properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesPsuGetProperties(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Psu.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hPsu, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current power supply state
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPsu`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
ze_result_t ZE_APICALL
zesPsuGetState(
    zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
    zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Psu.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hPsu, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of all RAS error sets on a device
/// 
/// @details
///     - A RAS error set is a collection of RAS error counters of a given type
///       (correctable/uncorrectable) from hardware blocks contained within a
///       sub-device or within the device.
///     - A device without sub-devices will typically return two handles, one
///       for correctable errors sets and one for uncorrectable error sets.
///     - A device with sub-devices will return RAS error sets for each
///       sub-device and possibly RAS error sets for hardware blocks outside the
///       sub-devices.
///     - If the function completes successfully but pCount is set to 0, RAS
///       features are not available/enabled on this device.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumRasErrorSets(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumRasErrorSets = ze_lib::context->zesDdiTable.load()->Device.pfnEnumRasErrorSets;
    if( nullptr == pfnEnumRasErrorSets ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumRasErrorSets( hDevice, pCount, phRas );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS properties of a given RAS error set - this enables discovery
///        of the type of RAS error set (correctable/uncorrectable) and if
///        located on a sub-device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesRasGetProperties(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Ras.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hRas, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the configured
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be triggered.
///     - When a particular RAS uncorrectable error counter exceeds the
///       configured threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be triggered.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
ze_result_t ZE_APICALL
zesRasGetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                    ///< thresholds used to trigger events
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set RAS error thresholds that control when RAS events are generated
/// 
/// @details
///     - The driver maintains counters for all RAS error sets and error
///       categories. Events are generated when errors occur. The configuration
///       enables setting thresholds to limit when events are sent.
///     - When a particular RAS correctable error counter exceeds the specified
///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
///       be generated.
///     - When a particular RAS uncorrectable error counter exceeds the
///       specified threshold, the event
///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be generated.
///     - Call ::zesRasGetState() and set the clear flag to true to restart
///       event generation once counters have exceeded thresholds.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to set thresholds.
ze_result_t ZE_APICALL
zesRasSetConfig(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Ras.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hRas, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current value of RAS error counters for a particular error set
/// 
/// @details
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pState`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t ZE_APICALL
zesRasGetState(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
    zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Ras.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hRas, clear, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Returns handles to scheduler components.
/// 
/// @details
///     - Each scheduler component manages the distribution of work across one
///       or more accelerator engines.
///     - If an application wishes to change the scheduler behavior for all
///       accelerator engines of a specific type (e.g. compute), it should
///       select all the handles where the `engines` member
///       ::zes_sched_properties_t contains that type.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumSchedulers(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumSchedulers = ze_lib::context->zesDdiTable.load()->Device.pfnEnumSchedulers;
    if( nullptr == pfnEnumSchedulers ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumSchedulers( hDevice, pCount, phScheduler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get properties related to a scheduler component
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesSchedulerGetProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
    zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hScheduler, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get current scheduling mode in effect on a scheduler component.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetCurrentMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetCurrentMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetCurrentMode;
    if( nullptr == pfnGetCurrentMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetCurrentMode( hScheduler, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimeoutModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTimeoutModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimeoutModeProperties;
    if( nullptr == pfnGetTimeoutModeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
ze_result_t ZE_APICALL
zesSchedulerGetTimesliceModeProperties(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                    ///< this mode, otherwise it will return the current properties.
    zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetTimesliceModeProperties = ze_lib::context->zesDdiTable.load()->Scheduler.pfnGetTimesliceModeProperties;
    if( nullptr == pfnGetTimesliceModeProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
///        mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized for multiple applications or contexts
///       submitting work to the hardware. When higher priority work arrives,
///       the scheduler attempts to pause the current executing work within some
///       timeout interval, then submits the other work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimeoutMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetTimeoutMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimeoutMode;
    if( nullptr == pfnSetTimeoutMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
///        scheduler mode parameters if already running in this mode.
/// 
/// @details
///     - This mode is optimized to provide fair sharing of hardware execution
///       time between multiple contexts submitting work to the hardware
///       concurrently.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetTimesliceMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetTimesliceMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetTimesliceMode;
    if( nullptr == pfnSetTimesliceMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
/// 
/// @details
///     - This mode is optimized for single application/context use-cases. It
///       permits a context to run indefinitely on the hardware without being
///       preempted or terminated. All pending work for other contexts must wait
///       until the running context completes with no further submitted work.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetExclusiveMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetExclusiveMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetExclusiveMode;
    if( nullptr == pfnSetExclusiveMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetExclusiveMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
/// 
/// @details
///     - This is a special mode that must ben enabled when debugging an
///       application that uses this device e.g. using the Level0 Debug API.
///     - It ensures that only one command queue can execute work on the
///       hardware at a given time. Work is permitted to run as long as needed
///       without enforcing any scheduler fairness policies.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - [DEPRECATED] No longer supported.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hScheduler`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pNeedReload`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + This scheduler component does not support scheduler modes.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make this modification.
ze_result_t ZE_APICALL
zesSchedulerSetComputeUnitDebugMode(
    zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
    ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                    ///< apply the new scheduler mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetComputeUnitDebugMode = ze_lib::context->zesDdiTable.load()->Scheduler.pfnSetComputeUnitDebugMode;
    if( nullptr == pfnSetComputeUnitDebugMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of standby controls
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumStandbyDomains(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumStandbyDomains = ze_lib::context->zesDdiTable.load()->Device.pfnEnumStandbyDomains;
    if( nullptr == pfnEnumStandbyDomains ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get standby hardware component properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesStandbyGetProperties(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Standby.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hStandby, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the current standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMode`
ze_result_t ZE_APICALL
zesStandbyGetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnGetMode;
    if( nullptr == pfnGetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetMode( hStandby, pMode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set standby promotion mode
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hStandby`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_STANDBY_PROMO_MODE_NEVER < mode`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
ze_result_t ZE_APICALL
zesStandbySetMode(
    zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
    zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetMode = ze_lib::context->zesDdiTable.load()->Standby.pfnSetMode;
    if( nullptr == pfnSetMode ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetMode( hStandby, mode );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of temperature sensors
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumTemperatureSensors(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumTemperatureSensors = ze_lib::context->zesDdiTable.load()->Device.pfnEnumTemperatureSensors;
    if( nullptr == pfnEnumTemperatureSensors ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature sensor properties
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesTemperatureGetProperties(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetProperties = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetProperties;
    if( nullptr == pfnGetProperties ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetProperties( hTemperature, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get temperature configuration for this sensor - which events are
///        triggered and the trigger conditions
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally this is only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL.
///         + One or both of the thresholds is not supported. Check the `isThreshold1Supported` and `isThreshold2Supported` members of ::zes_temp_properties_t.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
ze_result_t ZE_APICALL
zesTemperatureGetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetConfig;
    if( nullptr == pfnGetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set temperature configuration for this sensor - indicates which events
///        are triggered and the trigger conditions
/// 
/// @details
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL will be triggered when
///       temperature reaches the critical range. Use the function
///       ::zesDeviceEventRegister() to start receiving this event.
///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1 and
///       ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD2 will be generated when
///       temperature cross the thresholds set using this function. Use the
///       function ::zesDeviceEventRegister() to start receiving these events.
///     - Only one running process can set the temperature configuration at a
///       time. If another process attempts to change the configuration, the
///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
///       ::zesTemperatureGetConfig() will return the process ID currently
///       controlling these settings.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pConfig`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///         + Temperature thresholds are not supported on this temperature sensor. Generally they are only supported for temperature sensor ::ZES_TEMP_SENSORS_GLOBAL.
///         + Enabling the critical temperature event is not supported. Check the `isCriticalTempSupported` member of ::zes_temp_properties_t.
///         + One or both of the thresholds is not supported. Check the `isThreshold1Supported` and `isThreshold2Supported` members of ::zes_temp_properties_t.
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to request this feature.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + Another running process is controlling these settings.
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + One or both the thresholds is above TjMax (see ::zesFrequencyOcGetTjMax()). Temperature thresholds must be below this value.
ze_result_t ZE_APICALL
zesTemperatureSetConfig(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    const zes_temp_config_t* pConfig                ///< [in] New configuration.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetConfig = ze_lib::context->zesDdiTable.load()->Temperature.pfnSetConfig;
    if( nullptr == pfnSetConfig ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetConfig( hTemperature, pConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the temperature from a specified sensor
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTemperature`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pTemperature`
ze_result_t ZE_APICALL
zesTemperatureGetState(
    zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
    double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                    ///< in degrees Celsius.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetState = ze_lib::context->zesDdiTable.load()->Temperature.pfnGetState;
    if( nullptr == pfnGetState ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetState( hTemperature, pTemperature );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get power limits
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function returns all the power limits associated with the
///       supplied power domain.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesPowerGetLimitsExt(
    zes_pwr_handle_t hPower,                        ///< [in] Power domain handle instance.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of power limit descriptors. If count is
                                                    ///< zero, then the driver shall update the value with the total number of
                                                    ///< components of this type that are available. If count is greater than
                                                    ///< the number of components of this type that are available, then the
                                                    ///< driver shall update the value with the correct number of components.
    zes_power_limit_ext_desc_t* pSustained          ///< [in,out][optional][range(0, *pCount)] Array of query results for power
                                                    ///< limit descriptors. If count is less than the number of components of
                                                    ///< this type that are available, then the driver shall only retrieve that
                                                    ///< number of components.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnGetLimitsExt;
    if( nullptr == pfnGetLimitsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetLimitsExt( hPower, pCount, pSustained );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set power limits
/// 
/// @details
///     - The application can only modify unlocked members of the limit
///       descriptors returned by ::zesPowerGetLimitsExt.
///     - Not all the limits returned by ::zesPowerGetLimitsExt need to be
///       supplied to this function.
///     - Limits do not have to be supplied in the same order as returned by
///       ::zesPowerGetLimitsExt.
///     - The same limit can be supplied multiple times. Limits are applied in
///       the order in which they are supplied.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hPower`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + User does not have permissions to make these modifications.
///     - ::ZE_RESULT_ERROR_NOT_AVAILABLE
///         + The device is in use, meaning that the GPU is under Over clocking, applying power limits under overclocking is not supported.
ze_result_t ZE_APICALL
zesPowerSetLimitsExt(
    zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
    zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetLimitsExt = ze_lib::context->zesDdiTable.load()->Power.pfnSetLimitsExt;
    if( nullptr == pfnSetLimitsExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetLimitsExt( hPower, pCount, pSustained );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get activity stats for Physical Function (PF) and each Virtual
///        Function (VF) associated with engine group.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hEngine`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE - "Engine activity extension is not supported in the environment."
ze_result_t ZE_APICALL
zesEngineGetActivityExt(
    zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_engine_stats_t* pStats                      ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector with engine stat for
                                                    ///< PF at index 0 of the vector followed by user provided pCount-1 number
                                                    ///< of VF engine stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetActivityExt = ze_lib::context->zesDdiTable.load()->Engine.pfnGetActivityExt;
    if( nullptr == pfnGetActivityExt ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetActivityExt( hEngine, pCount, pStats );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ras Get State
/// 
/// @details
///     - This function retrieves error counters for different RAS error
///       categories.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesRasGetStateExp(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of RAS state structures that can be retrieved.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of error categories for which state can be retrieved.
                                                    ///< if count is greater than the number of RAS states available, then the
                                                    ///< driver shall update the value with the correct number of RAS states available.
    zes_ras_state_exp_t* pState                     ///< [in,out][optional][range(0, *pCount)] array of query results for RAS
                                                    ///< error states for different categories.
                                                    ///< if count is less than the number of RAS states available, then driver
                                                    ///< shall only retrieve that number of RAS states.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnGetStateExp;
    if( nullptr == pfnGetStateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetStateExp( hRas, pCount, pState );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Ras Clear State
/// 
/// @details
///     - This function clears error counters for a RAS error category.
///     - Clearing errors will affect other threads/applications - the counter
///       values will start from zero.
///     - Clearing errors requires write permissions.
///     - The application should not call this function from simultaneous
///       threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hRas`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `::ZES_RAS_ERROR_CATEGORY_EXP_L3FABRIC_ERRORS < category`
///     - ::ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS
///         + Don't have permissions to clear error counters.
ze_result_t ZE_APICALL
zesRasClearStateExp(
    zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
    zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnClearStateExp = ze_lib::context->zesDdiTable.load()->RasExp.pfnClearStateExp;
    if( nullptr == pfnClearStateExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnClearStateExp( hRas, category );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get the firmware security version number of the currently running
///        firmware
/// 
/// @details
///     - The application should create a character array of size
///       ::ZES_STRING_PROPERTY_SIZE and reference it for the `pVersion`
///       parameter.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pVersion`
ze_result_t ZE_APICALL
zesFirmwareGetSecurityVersionExp(
    zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
    char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                    ///< returned if this property cannot be determined.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnGetSecurityVersionExp;
    if( nullptr == pfnGetSecurityVersionExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSecurityVersionExp( hFirmware, pVersion );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set the firmware security version number
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hFirmware`
ze_result_t ZE_APICALL
zesFirmwareSetSecurityVersionExp(
    zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetSecurityVersionExp = ze_lib::context->zesDdiTable.load()->FirmwareExp.pfnSetSecurityVersionExp;
    if( nullptr == pfnSetSecurityVersionExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetSecurityVersionExp( hFirmware );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sub device properties for the given sysman device handle
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceGetSubDevicePropertiesExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub devices.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of sub devices currently attached to the device.
                                                    ///< if count is greater than the number of sub devices currently attached
                                                    ///< to the device, then the driver shall update the value with the correct
                                                    ///< number of sub devices.
    zes_subdevice_exp_properties_t* pSubdeviceProps ///< [in,out][optional][range(0, *pCount)] array of sub device property structures.
                                                    ///< if count is less than the number of sysman sub devices available, then
                                                    ///< the driver shall only retrieve that number of sub device property structures.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetSubDevicePropertiesExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnGetSubDevicePropertiesExp;
    if( nullptr == pfnGetSubDevicePropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves sysman device and subdevice index for the given UUID and
///        sysman driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == phDevice`
///         + `nullptr == onSubdevice`
///         + `nullptr == subdeviceId`
ze_result_t ZE_APICALL
zesDriverGetDeviceByUuidExp(
    zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
    zes_uuid_t uuid,                                ///< [in] universal unique identifier.
    zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
    ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                    ///< UUID belongs to the root device.
    uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetDeviceByUuidExp = ze_lib::context->zesDdiTable.load()->DriverExp.pfnGetDeviceByUuidExp;
    if( nullptr == pfnGetDeviceByUuidExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of virtual function modules
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use ::zesDeviceEnumEnabledVFExp.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumActiveVFExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumActiveVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumActiveVFExp;
    if( nullptr == pfnEnumActiveVFExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get virtual function management properties
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFCapabilitiesExp.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pProperties`
ze_result_t ZE_APICALL
zesVFManagementGetVFPropertiesExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
    zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFPropertiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFPropertiesExp;
    if( nullptr == pfnGetVFPropertiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFPropertiesExp( hVFhandle, pProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory activity stats for each available memory types associated
///        with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFMemoryUtilizationExp2.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFMemoryUtilizationExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of memory stats available.
                                                    ///<  - if count is greater than the total number of memory stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of memory stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_vf_util_mem_exp_t* pMemUtil                 ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                    ///<  - if count is less than the total number of memory stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< memory stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFMemoryUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp;
    if( nullptr == pfnGetVFMemoryUtilizationExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine activity stats for each available engine group associated
///        with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported. Use
///       ::zesVFManagementGetVFEngineUtilizationExp2.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFEngineUtilizationExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
                                                    ///<  - The count returned is the sum of number of VF instances currently
                                                    ///< available and the PF instance.
    zes_vf_util_engine_exp_t* pEngineUtil           ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< engine stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFEngineUtilizationExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp;
    if( nullptr == pfnGetVFEngineUtilizationExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Configure utilization telemetry enabled or disabled associated with
///        Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < flags`
ze_result_t ZE_APICALL
zesVFManagementSetVFTelemetryModeExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                    ///< combination of ::zes_vf_info_util_exp_flag_t.
    ze_bool_t enable                                ///< [in] Enable utilization telemetry.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFTelemetryModeExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetryModeExp;
    if( nullptr == pfnSetVFTelemetryModeExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Set sampling interval to monitor for a particular utilization
///        telemetry associated with Virtual Function (VF)
/// 
/// @details
///     - [DEPRECATED] No longer supported.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + `0xf < flag`
ze_result_t ZE_APICALL
zesVFManagementSetVFTelemetrySamplingIntervalExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                    ///< combination of ::zes_vf_info_util_exp_flag_t.
    uint64_t samplingInterval                       ///< [in] Sampling interval value.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnSetVFTelemetrySamplingIntervalExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp;
    if( nullptr == pfnSetVFTelemetrySamplingIntervalExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get handle of virtual function modules
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesDeviceEnumEnabledVFExp(
    zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
    uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                    ///< if count is zero, then the driver shall update the value with the
                                                    ///< total number of components of this type that are available.
                                                    ///< if count is greater than the number of components of this type that
                                                    ///< are available, then the driver shall update the value with the correct
                                                    ///< number of components.
    zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                    ///< this type.
                                                    ///< if count is less than the number of components of this type that are
                                                    ///< available, then the driver shall only retrieve that number of
                                                    ///< component handles.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnEnumEnabledVFExp = ze_lib::context->zesDdiTable.load()->DeviceExp.pfnEnumEnabledVFExp;
    if( nullptr == pfnEnumEnabledVFExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get virtual function management capabilities
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCapability`
ze_result_t ZE_APICALL
zesVFManagementGetVFCapabilitiesExp(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
    zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFCapabilitiesExp = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFCapabilitiesExp;
    if( nullptr == pfnGetVFCapabilitiesExp ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFCapabilitiesExp( hVFhandle, pCapability );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get memory activity stats for each available memory types associated
///        with Virtual Function (VF)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - If VF is disable/pause/not active, utilization will give zero value.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFMemoryUtilizationExp2(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of memory stats available.
                                                    ///<  - if count is greater than the total number of memory stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of memory stats available.
    zes_vf_util_mem_exp2_t* pMemUtil                ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                    ///<  - if count is less than the total number of memory stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< memory stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFMemoryUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFMemoryUtilizationExp2;
    if( nullptr == pfnGetVFMemoryUtilizationExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get engine activity stats for each available engine group associated
///        with Virtual Function (VF)
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - If VF is disable/pause/not active, utilization will give zero value.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hVFhandle`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
ze_result_t ZE_APICALL
zesVFManagementGetVFEngineUtilizationExp2(
    zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
    uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                    ///<  - if count is zero, the driver shall update the value with the total
                                                    ///< number of engine stats available.
                                                    ///<  - if count is greater than the total number of engine stats
                                                    ///< available, the driver shall update the value with the correct number
                                                    ///< of engine stats available.
    zes_vf_util_engine_exp2_t* pEngineUtil          ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                    ///<  - if count is less than the total number of engine stats available,
                                                    ///< then driver shall only retrieve that number of stats.
                                                    ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                    ///< engine stats.
    )
{
    if(ze_lib::context->inTeardown) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    auto pfnGetVFEngineUtilizationExp2 = ze_lib::context->zesDdiTable.load()->VFManagementExp.pfnGetVFEngineUtilizationExp2;
    if( nullptr == pfnGetVFEngineUtilizationExp2 ) {
        if(!ze_lib::context->isInitialized)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        else
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );
}

} // extern "C"
