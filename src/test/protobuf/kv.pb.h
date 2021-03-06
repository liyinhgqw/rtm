// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kv.proto

#ifndef PROTOBUF_kv_2eproto__INCLUDED
#define PROTOBUF_kv_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace examples {
namespace kv {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_kv_2eproto();
void protobuf_AssignDesc_kv_2eproto();
void protobuf_ShutdownFile_kv_2eproto();

class KV;
class GetRequest;
class GetResponse;
class PutRequest;
class PutResponse;

// ===================================================================

class KV : public ::google::protobuf::Message {
 public:
  KV();
  virtual ~KV();
  
  KV(const KV& from);
  
  inline KV& operator=(const KV& from) {
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
  static const KV& default_instance();
  
  void Swap(KV* other);
  
  // implements Message ----------------------------------------------
  
  KV* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KV& from);
  void MergeFrom(const KV& from);
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
  
  // required string key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const char* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  
  // required string value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const char* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  
  // @@protoc_insertion_point(class_scope:examples.kv.KV)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* key_;
  ::std::string* value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2eproto();
  friend void protobuf_AssignDesc_kv_2eproto();
  friend void protobuf_ShutdownFile_kv_2eproto();
  
  void InitAsDefaultInstance();
  static KV* default_instance_;
};
// -------------------------------------------------------------------

class GetRequest : public ::google::protobuf::Message {
 public:
  GetRequest();
  virtual ~GetRequest();
  
  GetRequest(const GetRequest& from);
  
  inline GetRequest& operator=(const GetRequest& from) {
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
  static const GetRequest& default_instance();
  
  void Swap(GetRequest* other);
  
  // implements Message ----------------------------------------------
  
  GetRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetRequest& from);
  void MergeFrom(const GetRequest& from);
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
  
  // required string key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const char* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  
  // @@protoc_insertion_point(class_scope:examples.kv.GetRequest)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* key_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2eproto();
  friend void protobuf_AssignDesc_kv_2eproto();
  friend void protobuf_ShutdownFile_kv_2eproto();
  
  void InitAsDefaultInstance();
  static GetRequest* default_instance_;
};
// -------------------------------------------------------------------

class GetResponse : public ::google::protobuf::Message {
 public:
  GetResponse();
  virtual ~GetResponse();
  
  GetResponse(const GetResponse& from);
  
  inline GetResponse& operator=(const GetResponse& from) {
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
  static const GetResponse& default_instance();
  
  void Swap(GetResponse* other);
  
  // implements Message ----------------------------------------------
  
  GetResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetResponse& from);
  void MergeFrom(const GetResponse& from);
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
  
  // required string value = 1;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 1;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const char* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  
  // @@protoc_insertion_point(class_scope:examples.kv.GetResponse)
 private:
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2eproto();
  friend void protobuf_AssignDesc_kv_2eproto();
  friend void protobuf_ShutdownFile_kv_2eproto();
  
  void InitAsDefaultInstance();
  static GetResponse* default_instance_;
};
// -------------------------------------------------------------------

class PutRequest : public ::google::protobuf::Message {
 public:
  PutRequest();
  virtual ~PutRequest();
  
  PutRequest(const PutRequest& from);
  
  inline PutRequest& operator=(const PutRequest& from) {
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
  static const PutRequest& default_instance();
  
  void Swap(PutRequest* other);
  
  // implements Message ----------------------------------------------
  
  PutRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PutRequest& from);
  void MergeFrom(const PutRequest& from);
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
  
  // required string key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const char* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  
  // required string value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const char* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  
  // @@protoc_insertion_point(class_scope:examples.kv.PutRequest)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* key_;
  ::std::string* value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2eproto();
  friend void protobuf_AssignDesc_kv_2eproto();
  friend void protobuf_ShutdownFile_kv_2eproto();
  
  void InitAsDefaultInstance();
  static PutRequest* default_instance_;
};
// -------------------------------------------------------------------

class PutResponse : public ::google::protobuf::Message {
 public:
  PutResponse();
  virtual ~PutResponse();
  
  PutResponse(const PutResponse& from);
  
  inline PutResponse& operator=(const PutResponse& from) {
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
  static const PutResponse& default_instance();
  
  void Swap(PutResponse* other);
  
  // implements Message ----------------------------------------------
  
  PutResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PutResponse& from);
  void MergeFrom(const PutResponse& from);
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
  
  // required bool ret = 1;
  inline bool has_ret() const;
  inline void clear_ret();
  static const int kRetFieldNumber = 1;
  inline bool ret() const;
  inline void set_ret(bool value);
  
  // @@protoc_insertion_point(class_scope:examples.kv.PutResponse)
 private:
  inline void set_has_ret();
  inline void clear_has_ret();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  bool ret_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2eproto();
  friend void protobuf_AssignDesc_kv_2eproto();
  friend void protobuf_ShutdownFile_kv_2eproto();
  
  void InitAsDefaultInstance();
  static PutResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// KV

// required string key = 1;
inline bool KV::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KV::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KV::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KV::clear_key() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& KV::key() const {
  return *key_;
}
inline void KV::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void KV::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void KV::set_key(const char* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* KV::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  return key_;
}
inline ::std::string* KV::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required string value = 2;
inline bool KV::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KV::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KV::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KV::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& KV::value() const {
  return *value_;
}
inline void KV::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void KV::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void KV::set_value(const char* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* KV::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* KV::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// GetRequest

// required string key = 1;
inline bool GetRequest::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetRequest::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetRequest::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetRequest::clear_key() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& GetRequest::key() const {
  return *key_;
}
inline void GetRequest::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void GetRequest::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void GetRequest::set_key(const char* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* GetRequest::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  return key_;
}
inline ::std::string* GetRequest::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// GetResponse

// required string value = 1;
inline bool GetResponse::has_value() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetResponse::set_has_value() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetResponse::clear_has_value() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetResponse::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& GetResponse::value() const {
  return *value_;
}
inline void GetResponse::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void GetResponse::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void GetResponse::set_value(const char* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* GetResponse::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* GetResponse::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// PutRequest

// required string key = 1;
inline bool PutRequest::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PutRequest::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PutRequest::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PutRequest::clear_key() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& PutRequest::key() const {
  return *key_;
}
inline void PutRequest::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void PutRequest::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void PutRequest::set_key(const char* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PutRequest::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  return key_;
}
inline ::std::string* PutRequest::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required string value = 2;
inline bool PutRequest::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PutRequest::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PutRequest::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PutRequest::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& PutRequest::value() const {
  return *value_;
}
inline void PutRequest::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void PutRequest::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void PutRequest::set_value(const char* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* PutRequest::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* PutRequest::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// PutResponse

// required bool ret = 1;
inline bool PutResponse::has_ret() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PutResponse::set_has_ret() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PutResponse::clear_has_ret() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PutResponse::clear_ret() {
  ret_ = false;
  clear_has_ret();
}
inline bool PutResponse::ret() const {
  return ret_;
}
inline void PutResponse::set_ret(bool value) {
  set_has_ret();
  ret_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace kv
}  // namespace examples

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_kv_2eproto__INCLUDED
