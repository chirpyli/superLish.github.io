#[derive(Clone, PartialEq, ::prost::Message)]
pub struct Hello {
    #[prost(uint64, tag = "1")]
    pub nodeid: u64,
}
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct RouteTable {
    #[prost(uint64, tag = "1")]
    pub nodeid: u64,
    #[prost(message, repeated, tag = "2")]
    pub item: ::std::vec::Vec<RouteItem>,
}
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct RouteItem {
    #[prost(uint64, tag = "1")]
    pub dst: u64,
    #[prost(uint64, tag = "2")]
    pub next: u64,
    #[prost(uint64, tag = "3")]
    pub distance: u64,
}
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct RouteMessage {
    #[prost(uint64, tag = "1")]
    pub src: u64,
    #[prost(uint64, tag = "2")]
    pub dst: u64,
    #[prost(bytes, tag = "3")]
    pub payload: std::vec::Vec<u8>,
}
#[derive(Clone, PartialEq, ::prost::Message)]
pub struct RouteAck {
    #[prost(uint64, tag = "1")]
    pub src: u64,
    #[prost(uint64, tag = "2")]
    pub dst: u64,
    #[prost(uint32, tag = "3")]
    pub result: u32,
}
#[doc = r" Generated client implementations."]
pub mod network_client {
    #![allow(unused_variables, dead_code, missing_docs)]
    use tonic::codegen::*;
    pub struct NetworkClient<T> {
        inner: tonic::client::Grpc<T>,
    }
    impl NetworkClient<tonic::transport::Channel> {
        #[doc = r" Attempt to create a new client by connecting to a given endpoint."]
        pub async fn connect<D>(dst: D) -> Result<Self, tonic::transport::Error>
        where
            D: std::convert::TryInto<tonic::transport::Endpoint>,
            D::Error: Into<StdError>,
        {
            let conn = tonic::transport::Endpoint::new(dst)?.connect().await?;
            Ok(Self::new(conn))
        }
    }
    impl<T> NetworkClient<T>
    where
        T: tonic::client::GrpcService<tonic::body::BoxBody>,
        T::ResponseBody: Body + HttpBody + Send + 'static,
        T::Error: Into<StdError>,
        <T::ResponseBody as HttpBody>::Error: Into<StdError> + Send,
    {
        pub fn new(inner: T) -> Self {
            let inner = tonic::client::Grpc::new(inner);
            Self { inner }
        }
        pub fn with_interceptor(inner: T, interceptor: impl Into<tonic::Interceptor>) -> Self {
            let inner = tonic::client::Grpc::with_interceptor(inner, interceptor);
            Self { inner }
        }
        pub async fn hello(
            &mut self,
            request: impl tonic::IntoRequest<super::Hello>,
        ) -> Result<tonic::Response<super::Hello>, tonic::Status> {
            self.inner.ready().await.map_err(|e| {
                tonic::Status::new(
                    tonic::Code::Unknown,
                    format!("Service was not ready: {}", e.into()),
                )
            })?;
            let codec = tonic::codec::ProstCodec::default();
            let path = http::uri::PathAndQuery::from_static("/netproto.Network/hello");
            self.inner.unary(request.into_request(), path, codec).await
        }
        pub async fn pull_route_table(
            &mut self,
            request: impl tonic::IntoRequest<super::RouteTable>,
        ) -> Result<tonic::Response<super::RouteTable>, tonic::Status> {
            self.inner.ready().await.map_err(|e| {
                tonic::Status::new(
                    tonic::Code::Unknown,
                    format!("Service was not ready: {}", e.into()),
                )
            })?;
            let codec = tonic::codec::ProstCodec::default();
            let path = http::uri::PathAndQuery::from_static("/netproto.Network/pull_route_table");
            self.inner.unary(request.into_request(), path, codec).await
        }
        pub async fn route_message(
            &mut self,
            request: impl tonic::IntoRequest<super::RouteMessage>,
        ) -> Result<tonic::Response<super::RouteAck>, tonic::Status> {
            self.inner.ready().await.map_err(|e| {
                tonic::Status::new(
                    tonic::Code::Unknown,
                    format!("Service was not ready: {}", e.into()),
                )
            })?;
            let codec = tonic::codec::ProstCodec::default();
            let path = http::uri::PathAndQuery::from_static("/netproto.Network/route_message");
            self.inner.unary(request.into_request(), path, codec).await
        }
    }
    impl<T: Clone> Clone for NetworkClient<T> {
        fn clone(&self) -> Self {
            Self {
                inner: self.inner.clone(),
            }
        }
    }
    impl<T> std::fmt::Debug for NetworkClient<T> {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "NetworkClient {{ ... }}")
        }
    }
}
#[doc = r" Generated server implementations."]
pub mod network_server {
    #![allow(unused_variables, dead_code, missing_docs)]
    use tonic::codegen::*;
    #[doc = "Generated trait containing gRPC methods that should be implemented for use with NetworkServer."]
    #[async_trait]
    pub trait Network: Send + Sync + 'static {
        async fn hello(
            &self,
            request: tonic::Request<super::Hello>,
        ) -> Result<tonic::Response<super::Hello>, tonic::Status>;
        async fn pull_route_table(
            &self,
            request: tonic::Request<super::RouteTable>,
        ) -> Result<tonic::Response<super::RouteTable>, tonic::Status>;
        async fn route_message(
            &self,
            request: tonic::Request<super::RouteMessage>,
        ) -> Result<tonic::Response<super::RouteAck>, tonic::Status>;
    }
    #[derive(Debug)]
    #[doc(hidden)]
    pub struct NetworkServer<T: Network> {
        inner: _Inner<T>,
    }
    struct _Inner<T>(Arc<T>, Option<tonic::Interceptor>);
    impl<T: Network> NetworkServer<T> {
        pub fn new(inner: T) -> Self {
            let inner = Arc::new(inner);
            let inner = _Inner(inner, None);
            Self { inner }
        }
        pub fn with_interceptor(inner: T, interceptor: impl Into<tonic::Interceptor>) -> Self {
            let inner = Arc::new(inner);
            let inner = _Inner(inner, Some(interceptor.into()));
            Self { inner }
        }
    }
    impl<T, B> Service<http::Request<B>> for NetworkServer<T>
    where
        T: Network,
        B: HttpBody + Send + Sync + 'static,
        B::Error: Into<StdError> + Send + 'static,
    {
        type Response = http::Response<tonic::body::BoxBody>;
        type Error = Never;
        type Future = BoxFuture<Self::Response, Self::Error>;
        fn poll_ready(&mut self, _cx: &mut Context<'_>) -> Poll<Result<(), Self::Error>> {
            Poll::Ready(Ok(()))
        }
        fn call(&mut self, req: http::Request<B>) -> Self::Future {
            let inner = self.inner.clone();
            match req.uri().path() {
                "/netproto.Network/hello" => {
                    #[allow(non_camel_case_types)]
                    struct helloSvc<T: Network>(pub Arc<T>);
                    impl<T: Network> tonic::server::UnaryService<super::Hello> for helloSvc<T> {
                        type Response = super::Hello;
                        type Future = BoxFuture<tonic::Response<Self::Response>, tonic::Status>;
                        fn call(&mut self, request: tonic::Request<super::Hello>) -> Self::Future {
                            let inner = self.0.clone();
                            let fut = async move { inner.hello(request).await };
                            Box::pin(fut)
                        }
                    }
                    let inner = self.inner.clone();
                    let fut = async move {
                        let interceptor = inner.1.clone();
                        let inner = inner.0;
                        let method = helloSvc(inner);
                        let codec = tonic::codec::ProstCodec::default();
                        let mut grpc = if let Some(interceptor) = interceptor {
                            tonic::server::Grpc::with_interceptor(codec, interceptor)
                        } else {
                            tonic::server::Grpc::new(codec)
                        };
                        let res = grpc.unary(method, req).await;
                        Ok(res)
                    };
                    Box::pin(fut)
                }
                "/netproto.Network/pull_route_table" => {
                    #[allow(non_camel_case_types)]
                    struct pull_route_tableSvc<T: Network>(pub Arc<T>);
                    impl<T: Network> tonic::server::UnaryService<super::RouteTable> for pull_route_tableSvc<T> {
                        type Response = super::RouteTable;
                        type Future = BoxFuture<tonic::Response<Self::Response>, tonic::Status>;
                        fn call(
                            &mut self,
                            request: tonic::Request<super::RouteTable>,
                        ) -> Self::Future {
                            let inner = self.0.clone();
                            let fut = async move { inner.pull_route_table(request).await };
                            Box::pin(fut)
                        }
                    }
                    let inner = self.inner.clone();
                    let fut = async move {
                        let interceptor = inner.1.clone();
                        let inner = inner.0;
                        let method = pull_route_tableSvc(inner);
                        let codec = tonic::codec::ProstCodec::default();
                        let mut grpc = if let Some(interceptor) = interceptor {
                            tonic::server::Grpc::with_interceptor(codec, interceptor)
                        } else {
                            tonic::server::Grpc::new(codec)
                        };
                        let res = grpc.unary(method, req).await;
                        Ok(res)
                    };
                    Box::pin(fut)
                }
                "/netproto.Network/route_message" => {
                    #[allow(non_camel_case_types)]
                    struct route_messageSvc<T: Network>(pub Arc<T>);
                    impl<T: Network> tonic::server::UnaryService<super::RouteMessage> for route_messageSvc<T> {
                        type Response = super::RouteAck;
                        type Future = BoxFuture<tonic::Response<Self::Response>, tonic::Status>;
                        fn call(
                            &mut self,
                            request: tonic::Request<super::RouteMessage>,
                        ) -> Self::Future {
                            let inner = self.0.clone();
                            let fut = async move { inner.route_message(request).await };
                            Box::pin(fut)
                        }
                    }
                    let inner = self.inner.clone();
                    let fut = async move {
                        let interceptor = inner.1.clone();
                        let inner = inner.0;
                        let method = route_messageSvc(inner);
                        let codec = tonic::codec::ProstCodec::default();
                        let mut grpc = if let Some(interceptor) = interceptor {
                            tonic::server::Grpc::with_interceptor(codec, interceptor)
                        } else {
                            tonic::server::Grpc::new(codec)
                        };
                        let res = grpc.unary(method, req).await;
                        Ok(res)
                    };
                    Box::pin(fut)
                }
                _ => Box::pin(async move {
                    Ok(http::Response::builder()
                        .status(200)
                        .header("grpc-status", "12")
                        .body(tonic::body::BoxBody::empty())
                        .unwrap())
                }),
            }
        }
    }
    impl<T: Network> Clone for NetworkServer<T> {
        fn clone(&self) -> Self {
            let inner = self.inner.clone();
            Self { inner }
        }
    }
    impl<T: Network> Clone for _Inner<T> {
        fn clone(&self) -> Self {
            Self(self.0.clone(), self.1.clone())
        }
    }
    impl<T: std::fmt::Debug> std::fmt::Debug for _Inner<T> {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "{:?}", self.0)
        }
    }
    impl<T: Network> tonic::transport::NamedService for NetworkServer<T> {
        const NAME: &'static str = "netproto.Network";
    }
}
