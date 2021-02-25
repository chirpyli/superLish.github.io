#[macro_use]
extern crate log;

mod host;
mod netproto;

use host::*;
use netproto::RouteMessage;
use std::collections::HashMap;
use std::env;
/*
1. 运行时输入 router nodeid, 例如节点id=1，则输入router 1, 监听端口为30000+id值，
2. 忽略参数合法性检测，相关错误处理被忽略.
3. 因没有连接失败错误处理，需要延时进行连接任务
4. 简单测试，输入route <id-value>, 目前id-value值为[0..5]
*/

fn main() {
    init_logger();
    let cmd: Vec<String> = env::args().collect();
    info!("cmd args: {:?}", cmd);
    let nodeid: u64 = cmd[1].parse().unwrap();
    info!("local nodeid: {}", nodeid);

    let mut runtime = tokio::runtime::Builder::new()
        .basic_scheduler()
        .enable_all()
        .build()
        .unwrap();
    runtime.block_on(run(nodeid));
}

async fn run(nodeid: u64) {
    let host = Host::new(nodeid);
    let connect_nodes = create_test_connect_table();
    let conn_host = host.clone();
    tokio::spawn(async move {
        tokio::time::delay_for(tokio::time::Duration::from_millis(80 * 1000)).await;
        conn_host.connect_nodes(connect_nodes).await;
    });

    let timer_host = host.clone();
    tokio::spawn(async move {
        tokio::time::delay_for(tokio::time::Duration::from_millis(100 * 1000)).await;
        timer_host.timer_task().await;
    });

    // 测试从节点4发送到节点5
    if nodeid == 4 {
        let route_host = host.clone();
        tokio::spawn(async move {
            tokio::time::delay_for(tokio::time::Duration::from_millis(150 * 1000)).await;
            let message = RouteMessage {
                dst: 5,
                src: 4,
                payload: vec![1, 2, 3],
            };
            route_host.send_route_message(message).await;
        });
    }

    host.start().await;
}

fn init_logger() {
    simple_logger::init_with_level(log::Level::Info).unwrap();
}

// 测试用 图连接，邻接列表
fn create_test_connect_table() -> HashMap<NodeId, Vec<NodeId>> {
    let mut table = HashMap::new();
    let n0 = vec![4, 1, 2];
    let n1 = vec![0, 3, 4];
    let n2 = vec![0, 3, 5];
    let n3 = vec![1, 2, 5];
    let n4 = vec![1, 0];
    let n5 = vec![2, 3];

    table.insert(0, n0);
    table.insert(1, n1);
    table.insert(2, n2);
    table.insert(3, n3);
    table.insert(4, n4);
    table.insert(5, n5);

    table
}
