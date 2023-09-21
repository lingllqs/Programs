mod my {
    //
    pub struct OpenBox<T> {
        pub contents: T,
    }

    #[allow(dead_code)]
    pub struct CloseBox<T> {
        contents: T,
    }
}
