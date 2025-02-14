// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: transaction.proto
#ifndef GRPC_transaction_2eproto__INCLUDED
#define GRPC_transaction_2eproto__INCLUDED

#include "transaction.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace transaction {

class TransactionService final {
 public:
  static constexpr char const* service_full_name() {
    return "transaction.TransactionService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::transaction::TransactionResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>> AsyncAddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>>(AsyncAddTransactionRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>> PrepareAsyncAddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>>(PrepareAsyncAddTransactionRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>* AsyncAddTransactionRaw(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::transaction::TransactionResponse>* PrepareAsyncAddTransactionRaw(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::transaction::TransactionResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>> AsyncAddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>>(AsyncAddTransactionRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>> PrepareAsyncAddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>>(PrepareAsyncAddTransactionRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response, std::function<void(::grpc::Status)>) override;
      void AddTransaction(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>* AsyncAddTransactionRaw(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::transaction::TransactionResponse>* PrepareAsyncAddTransactionRaw(::grpc::ClientContext* context, const ::transaction::TransactionJsonRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_AddTransaction_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status AddTransaction(::grpc::ServerContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_AddTransaction() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAddTransaction(::grpc::ServerContext* context, ::transaction::TransactionJsonRequest* request, ::grpc::ServerAsyncResponseWriter< ::transaction::TransactionResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_AddTransaction<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_AddTransaction() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::transaction::TransactionJsonRequest, ::transaction::TransactionResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::transaction::TransactionJsonRequest* request, ::transaction::TransactionResponse* response) { return this->AddTransaction(context, request, response); }));}
    void SetMessageAllocatorFor_AddTransaction(
        ::grpc::MessageAllocator< ::transaction::TransactionJsonRequest, ::transaction::TransactionResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::transaction::TransactionJsonRequest, ::transaction::TransactionResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AddTransaction(
      ::grpc::CallbackServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_AddTransaction<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_AddTransaction() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_AddTransaction() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAddTransaction(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_AddTransaction() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->AddTransaction(context, request, response); }));
    }
    ~WithRawCallbackMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* AddTransaction(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_AddTransaction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_AddTransaction() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::transaction::TransactionJsonRequest, ::transaction::TransactionResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::transaction::TransactionJsonRequest, ::transaction::TransactionResponse>* streamer) {
                       return this->StreamedAddTransaction(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_AddTransaction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status AddTransaction(::grpc::ServerContext* /*context*/, const ::transaction::TransactionJsonRequest* /*request*/, ::transaction::TransactionResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAddTransaction(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::transaction::TransactionJsonRequest,::transaction::TransactionResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_AddTransaction<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_AddTransaction<Service > StreamedService;
};

}  // namespace transaction


#endif  // GRPC_transaction_2eproto__INCLUDED
