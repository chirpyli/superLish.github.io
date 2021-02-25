fn main() {
    tonic_build::configure()
        .out_dir("./src")
        .compile(&["./proto/rpc.proto"], &["./proto"])
        .expect("failed to compile protos");
}