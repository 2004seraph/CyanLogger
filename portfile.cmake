vcpkg_from_github(
  OUT_SOURCE_PATH SOURCE_PATH
  REPO sammot/cyanlogger
  REF 66326ec7cb18cf943e7cc2ad7694bd04276338ad
  SHA512 85dc681b8bcaca6abe74f5e01a5cb09e24fbb565f66541737dc54306617ba1ab8cd919fcf0384700e6c4be3fce1ee1e23b62d3649a320f556b44cb2549393e7a
  HEAD_REF main
)

vcpkg_configure_cmake(
  SOURCE_PATH "${SOURCE_PATH}"
  PREFER_NINJA
)
vcpkg_install_cmake()
vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(
  INSTALL "${SOURCE_PATH}/LICENSE"
  DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
  RENAME copyright
)