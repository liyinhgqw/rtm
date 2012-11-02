// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_mset.proto

#ifndef PROTOBUF_google_2fprotobuf_2funittest_5fmset_2eproto__INCLUDED
#define PROTOBUF_google_2fprotobuf_2funittest_5fmset_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace protobuf_unittest {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();

class TestMessageSet;
class TestMessageSetContainer;
class TestMessageSetExtension1;
class TestMessageSetExtension2;
class RawMessageSet;
class RawMessageSet_Item;

// ===================================================================

class TestMessageSet : public ::google::protobuf::Message {
 public:
  TestMessageSet();
  virtual ~TestMessageSet();
  
  TestMessageSet(const TestMessageSet& from);
  
  inline TestMessageSet& operator=(const TestMessageSet& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMessageSet& default_instance();
  
  void Swap(TestMessageSet* other);
  
  // implements Message ----------------------------------------------
  
  TestMessageSet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestMessageSet& from);
  void MergeFrom(const TestMessageSet& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(TestMessageSet)
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestMessageSet)
 private:
  
  ::google::protobuf::internal::ExtensionSet _extensions_;
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static TestMessageSet* default_instance_;
};
// -------------------------------------------------------------------

class TestMessageSetContainer : public ::google::protobuf::Message {
 public:
  TestMessageSetContainer();
  virtual ~TestMessageSetContainer();
  
  TestMessageSetContainer(const TestMessageSetContainer& from);
  
  inline TestMessageSetContainer& operator=(const TestMessageSetContainer& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMessageSetContainer& default_instance();
  
  void Swap(TestMessageSetContainer* other);
  
  // implements Message ----------------------------------------------
  
  TestMessageSetContainer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestMessageSetContainer& from);
  void MergeFrom(const TestMessageSetContainer& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .protobuf_unittest.TestMessageSet message_set = 1;
  inline bool has_message_set() const;
  inline void clear_message_set();
  static const int kMessageSetFieldNumber = 1;
  inline const ::protobuf_unittest::TestMessageSet& message_set() const;
  inline ::protobuf_unittest::TestMessageSet* mutable_message_set();
  inline ::protobuf_unittest::TestMessageSet* release_message_set();
  
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestMessageSetContainer)
 private:
  inline void set_has_message_set();
  inline void clear_has_message_set();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::protobuf_unittest::TestMessageSet* message_set_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static TestMessageSetContainer* default_instance_;
};
// -------------------------------------------------------------------

class TestMessageSetExtension1 : public ::google::protobuf::Message {
 public:
  TestMessageSetExtension1();
  virtual ~TestMessageSetExtension1();
  
  TestMessageSetExtension1(const TestMessageSetExtension1& from);
  
  inline TestMessageSetExtension1& operator=(const TestMessageSetExtension1& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMessageSetExtension1& default_instance();
  
  void Swap(TestMessageSetExtension1* other);
  
  // implements Message ----------------------------------------------
  
  TestMessageSetExtension1* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestMessageSetExtension1& from);
  void MergeFrom(const TestMessageSetExtension1& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional int32 i = 15;
  inline bool has_i() const;
  inline void clear_i();
  static const int kIFieldNumber = 15;
  inline ::google::protobuf::int32 i() const;
  inline void set_i(::google::protobuf::int32 value);
  
  static const int kMessageSetExtensionFieldNumber = 1545008;
  static ::google::protobuf::internal::ExtensionIdentifier< ::protobuf_unittest::TestMessageSet,
      ::google::protobuf::internal::MessageTypeTraits< ::protobuf_unittest::TestMessageSetExtension1 >, 11, false >
    message_set_extension;
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestMessageSetExtension1)
 private:
  inline void set_has_i();
  inline void clear_has_i();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 i_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static TestMessageSetExtension1* default_instance_;
};
// -------------------------------------------------------------------

class TestMessageSetExtension2 : public ::google::protobuf::Message {
 public:
  TestMessageSetExtension2();
  virtual ~TestMessageSetExtension2();
  
  TestMessageSetExtension2(const TestMessageSetExtension2& from);
  
  inline TestMessageSetExtension2& operator=(const TestMessageSetExtension2& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const TestMessageSetExtension2& default_instance();
  
  void Swap(TestMessageSetExtension2* other);
  
  // implements Message ----------------------------------------------
  
  TestMessageSetExtension2* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TestMessageSetExtension2& from);
  void MergeFrom(const TestMessageSetExtension2& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string str = 25;
  inline bool has_str() const;
  inline void clear_str();
  static const int kStrFieldNumber = 25;
  inline const ::std::string& str() const;
  inline void set_str(const ::std::string& value);
  inline void set_str(const char* value);
  inline void set_str(const char* value, size_t size);
  inline ::std::string* mutable_str();
  inline ::std::string* release_str();
  
  static const int kMessageSetExtensionFieldNumber = 1547769;
  static ::google::protobuf::internal::ExtensionIdentifier< ::protobuf_unittest::TestMessageSet,
      ::google::protobuf::internal::MessageTypeTraits< ::protobuf_unittest::TestMessageSetExtension2 >, 11, false >
    message_set_extension;
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestMessageSetExtension2)
 private:
  inline void set_has_str();
  inline void clear_has_str();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* str_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static TestMessageSetExtension2* default_instance_;
};
// -------------------------------------------------------------------

class RawMessageSet_Item : public ::google::protobuf::Message {
 public:
  RawMessageSet_Item();
  virtual ~RawMessageSet_Item();
  
  RawMessageSet_Item(const RawMessageSet_Item& from);
  
  inline RawMessageSet_Item& operator=(const RawMessageSet_Item& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const RawMessageSet_Item& default_instance();
  
  void Swap(RawMessageSet_Item* other);
  
  // implements Message ----------------------------------------------
  
  RawMessageSet_Item* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RawMessageSet_Item& from);
  void MergeFrom(const RawMessageSet_Item& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required int32 type_id = 2;
  inline bool has_type_id() const;
  inline void clear_type_id();
  static const int kTypeIdFieldNumber = 2;
  inline ::google::protobuf::int32 type_id() const;
  inline void set_type_id(::google::protobuf::int32 value);
  
  // required bytes message = 3;
  inline bool has_message() const;
  inline void clear_message();
  static const int kMessageFieldNumber = 3;
  inline const ::std::string& message() const;
  inline void set_message(const ::std::string& value);
  inline void set_message(const char* value);
  inline void set_message(const void* value, size_t size);
  inline ::std::string* mutable_message();
  inline ::std::string* release_message();
  
  // @@protoc_insertion_point(class_scope:protobuf_unittest.RawMessageSet.Item)
 private:
  inline void set_has_type_id();
  inline void clear_has_type_id();
  inline void set_has_message();
  inline void clear_has_message();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* message_;
  ::google::protobuf::int32 type_id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static RawMessageSet_Item* default_instance_;
};
// -------------------------------------------------------------------

class RawMessageSet : public ::google::protobuf::Message {
 public:
  RawMessageSet();
  virtual ~RawMessageSet();
  
  RawMessageSet(const RawMessageSet& from);
  
  inline RawMessageSet& operator=(const RawMessageSet& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const RawMessageSet& default_instance();
  
  void Swap(RawMessageSet* other);
  
  // implements Message ----------------------------------------------
  
  RawMessageSet* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RawMessageSet& from);
  void MergeFrom(const RawMessageSet& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef RawMessageSet_Item Item;
  
  // accessors -------------------------------------------------------
  
  // repeated group Item = 1 {
  inline int item_size() const;
  inline void clear_item();
  static const int kItemFieldNumber = 1;
  inline const ::protobuf_unittest::RawMessageSet_Item& item(int index) const;
  inline ::protobuf_unittest::RawMessageSet_Item* mutable_item(int index);
  inline ::protobuf_unittest::RawMessageSet_Item* add_item();
  inline const ::google::protobuf::RepeatedPtrField< ::protobuf_unittest::RawMessageSet_Item >&
      item() const;
  inline ::google::protobuf::RepeatedPtrField< ::protobuf_unittest::RawMessageSet_Item >*
      mutable_item();
  
  // @@protoc_insertion_point(class_scope:protobuf_unittest.RawMessageSet)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::protobuf_unittest::RawMessageSet_Item > item_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fmset_2eproto();
  friend void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fmset_2eproto();
  
  void InitAsDefaultInstance();
  static RawMessageSet* default_instance_;
};
// ===================================================================


// ===================================================================

// TestMessageSet

// -------------------------------------------------------------------

// TestMessageSetContainer

// optional .protobuf_unittest.TestMessageSet message_set = 1;
inline bool TestMessageSetContainer::has_message_set() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TestMessageSetContainer::set_has_message_set() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TestMessageSetContainer::clear_has_message_set() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TestMessageSetContainer::clear_message_set() {
  if (message_set_ != NULL) message_set_->::protobuf_unittest::TestMessageSet::Clear();
  clear_has_message_set();
}
inline const ::protobuf_unittest::TestMessageSet& TestMessageSetContainer::message_set() const {
  return message_set_ != NULL ? *message_set_ : *default_instance_->message_set_;
}
inline ::protobuf_unittest::TestMessageSet* TestMessageSetContainer::mutable_message_set() {
  set_has_message_set();
  if (message_set_ == NULL) message_set_ = new ::protobuf_unittest::TestMessageSet;
  return message_set_;
}
inline ::protobuf_unittest::TestMessageSet* TestMessageSetContainer::release_message_set() {
  clear_has_message_set();
  ::protobuf_unittest::TestMessageSet* temp = message_set_;
  message_set_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// TestMessageSetExtension1

// optional int32 i = 15;
inline bool TestMessageSetExtension1::has_i() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TestMessageSetExtension1::set_has_i() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TestMessageSetExtension1::clear_has_i() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TestMessageSetExtension1::clear_i() {
  i_ = 0;
  clear_has_i();
}
inline ::google::protobuf::int32 TestMessageSetExtension1::i() const {
  return i_;
}
inline void TestMessageSetExtension1::set_i(::google::protobuf::int32 value) {
  set_has_i();
  i_ = value;
}

// -------------------------------------------------------------------

// TestMessageSetExtension2

// optional string str = 25;
inline bool TestMessageSetExtension2::has_str() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TestMessageSetExtension2::set_has_str() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TestMessageSetExtension2::clear_has_str() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TestMessageSetExtension2::clear_str() {
  if (str_ != &::google::protobuf::internal::kEmptyString) {
    str_->clear();
  }
  clear_has_str();
}
inline const ::std::string& TestMessageSetExtension2::str() const {
  return *str_;
}
inline void TestMessageSetExtension2::set_str(const ::std::string& value) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::kEmptyString) {
    str_ = new ::std::string;
  }
  str_->assign(value);
}
inline void TestMessageSetExtension2::set_str(const char* value) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::kEmptyString) {
    str_ = new ::std::string;
  }
  str_->assign(value);
}
inline void TestMessageSetExtension2::set_str(const char* value, size_t size) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::kEmptyString) {
    str_ = new ::std::string;
  }
  str_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TestMessageSetExtension2::mutable_str() {
  set_has_str();
  if (str_ == &::google::protobuf::internal::kEmptyString) {
    str_ = new ::std::string;
  }
  return str_;
}
inline ::std::string* TestMessageSetExtension2::release_str() {
  clear_has_str();
  if (str_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = str_;
    str_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// RawMessageSet_Item

// required int32 type_id = 2;
inline bool RawMessageSet_Item::has_type_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RawMessageSet_Item::set_has_type_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RawMessageSet_Item::clear_has_type_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RawMessageSet_Item::clear_type_id() {
  type_id_ = 0;
  clear_has_type_id();
}
inline ::google::protobuf::int32 RawMessageSet_Item::type_id() const {
  return type_id_;
}
inline void RawMessageSet_Item::set_type_id(::google::protobuf::int32 value) {
  set_has_type_id();
  type_id_ = value;
}

// required bytes message = 3;
inline bool RawMessageSet_Item::has_message() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RawMessageSet_Item::set_has_message() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RawMessageSet_Item::clear_has_message() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RawMessageSet_Item::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& RawMessageSet_Item::message() const {
  return *message_;
}
inline void RawMessageSet_Item::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void RawMessageSet_Item::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void RawMessageSet_Item::set_message(const void* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* RawMessageSet_Item::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* RawMessageSet_Item::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// RawMessageSet

// repeated group Item = 1 {
inline int RawMessageSet::item_size() const {
  return item_.size();
}
inline void RawMessageSet::clear_item() {
  item_.Clear();
}
inline const ::protobuf_unittest::RawMessageSet_Item& RawMessageSet::item(int index) const {
  return item_.Get(index);
}
inline ::protobuf_unittest::RawMessageSet_Item* RawMessageSet::mutable_item(int index) {
  return item_.Mutable(index);
}
inline ::protobuf_unittest::RawMessageSet_Item* RawMessageSet::add_item() {
  return item_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::protobuf_unittest::RawMessageSet_Item >&
RawMessageSet::item() const {
  return item_;
}
inline ::google::protobuf::RepeatedPtrField< ::protobuf_unittest::RawMessageSet_Item >*
RawMessageSet::mutable_item() {
  return &item_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf_unittest

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2funittest_5fmset_2eproto__INCLUDED
