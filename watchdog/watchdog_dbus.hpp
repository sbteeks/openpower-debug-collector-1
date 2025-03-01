#pragma once

#include <sdbusplus/bus.hpp>
#include <xyz/openbmc_project/Logging/Create/server.hpp>

#include <string>

namespace watchdog
{
namespace dump
{

enum ReturnCodes
{
    RC_SUCCESS = 0,
    RC_NOT_HANDLED = 1,
    RC_DBUS_ERROR = 2
};

using FFDCFormat =
    sdbusplus::xyz::openbmc_project::Logging::server::Create::FFDCFormat;

using FFDCTuple =
    std::tuple<FFDCFormat, uint8_t, uint8_t, sdbusplus::message::unix_fd>;

/**
 * @brief Create a dbus method
 *
 * Find the dbus service associated with the dbus object path and create
 * a dbus method for calling the specified dbus interface and function.
 *
 * @param path - dbus object path
 * @param interface - dbus method interface
 * @param function - dbus interface function
 * @param method - method that is created
 * @param extended - optional for extended methods
 * @return non-zero if error
 *
 **/
int dbusMethod(const std::string& path, const std::string& interface,
               const std::string& function, sdbusplus::message::message& method,
               const std::string& extended = "");

/**
 * @brief Create a PEL for the specified event type
 *
 * The additional data provided in the map will be placed in a user data
 * section of the PEL.
 *
 * @param  eventType - the event type
 * @param  additional - map of additional data
 * @param  ffdc - vector of ffdc data
 * @return Platform log id or 0 if error
 */
uint32_t createPel(const std::string& eventType,
                   std::map<std::string, std::string>& additional,
                   const std::vector<FFDCTuple>& ffdc);

} // namespace dump
} // namespace watchdog
