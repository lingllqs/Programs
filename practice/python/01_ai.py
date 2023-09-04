def get_response(question):
    # 问题与回答的映射关系
    qa_pairs = {
        "你叫什么名字": "我是 AI 机器人。",
        "你会编程吗": "是的，我会编程。",
        "你喜欢什么颜色": "我是一个机器人，没有感觉。",
        "再见": "再见，祝你有美好的一天！"
    }

    # 查找问题的回答
    response = qa_pairs.get(question)
    if response is not None:
        return response
    else:
        return "抱歉，我不知道如何回答这个问题。"


def main():
    print("你好，我是 AI 机器人。你可以问我任何问题，我会尽力回答。")
    while True:
        user_input = input("你: ")
        if user_input.lower() == "退出":
            print("再见！")
            break
        response = get_response(user_input)
        print("AI: " + response)


if __name__ == "__main__":
    main()
