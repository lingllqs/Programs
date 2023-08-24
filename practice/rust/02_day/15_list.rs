use std::cell::RefCell;
use std::rc::Rc;

// 定义一个结点结构体
#[derive(Clone)]
pub struct Node<T> {
    pub value: T,
    pub next: Option<Rc<RefCell<Node<T>>>>,
}

// 定义一个链表结构体
pub struct LinkedList<T> {
    pub head: Option<Rc<RefCell<Node<T>>>>,
}

impl<T> Node<T> {
    pub fn new(value: T) -> Rc<RefCell<Self>> {
        Rc::new(RefCell::new(Node { value, next: None }))
    }
}

impl<T> LinkedList<T> {
    pub fn new() -> Self {
        LinkedList { head: None }
    }

    // 插入节点
    pub fn push_front(&mut self, value: T) {
        let new_node = Node::new(value);

        match self.head.take() {
            None => {
                // 头结点为空
                self.head = Some(new_node.clone());
            }
            Some(old_head) => {
                // 头节点不为空
                new_node.borrow_mut().next = Some(old_head.clone());
                self.head = Some(new_node.clone());
            }
        }
    }
}

fn main() {
    let mut list = LinkedList::new();

    list.push_front("Rust");
    list.push_front("Python");
    list.push_front("C");

    // let mut current = list.head.clone();
    // while let Some(node) = current {
    //     let node_ref = node.borrow();
    //     print!("{} -> ", node_ref.value);
    //     current = node_ref.next.clone();
    // }

    // 打印链表
    let mut current = list.head.clone();
    let mut first_node = true;
    while let Some(node) = current {
        let node_ref = node.borrow();
        if first_node {
            first_node = false;
        } else {
            print!(" -> ");
        }
        print!("{}", node_ref.value);
        current = node_ref.next.clone();
    }
}
