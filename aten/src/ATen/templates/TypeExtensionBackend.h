#pragma once
#include <ATen/TypeDefault.h>

namespace at {

// For each function type that can be overriden, this dispatch class holds a
// static map in which function pointers are registered by schema.
// TODO: Check for invalid schemas prior to registration
struct CAFFE2_API ${Type}Dispatch {
  template<typename FnPtr>
  static FnPtr get_function(const std::string schema) {
    auto fn_table = get_fn_table<FnPtr>();
    auto it = fn_table.find(schema);
    if (it != fn_table.end()) {
      return it->second;
    }
    AT_ERROR("No function implemented for schema: ", schema);
  }

  template<typename FnPtr>
  static void register_function(const std::string schema, FnPtr fn) {
    get_fn_table<FnPtr>()[schema] = fn;
  }

  template<typename FnPtr>
  static std::map<std::string, FnPtr>& get_fn_table() {
    static std::map<std::string, FnPtr> fn_table;
    return fn_table;
  }
};

struct CAFFE2_API ${Type} : public TypeDefault {
  explicit ${Type}();

  Allocator* allocator() const override;
  Device getDeviceFromPtr(void * data) const override;
  std::unique_ptr<Generator> generator() const override;

  virtual ScalarType scalarType() const override;
  virtual caffe2::TypeMeta typeMeta() const override;
  virtual Backend backend() const override;
  virtual const char * toString() const override;
  virtual size_t elementSizeInBytes() const override;
  virtual TypeID ID() const override;

  ${type_method_declarations}
};

} // namespace at
