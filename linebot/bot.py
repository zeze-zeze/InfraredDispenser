from flask import Flask, request, abort

from linebot import (
    LineBotApi, WebhookHandler
)
from linebot.exceptions import (
    InvalidSignatureError
)
from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage,
)

app = Flask(__name__)

line_bot_api = LineBotApi('O47pe8FMhSs8MCZvYwLiRuB9r0Z2qf3Ik3ByHgu3WDm5qssFlkBfR5rvRwuQS61hAXOIrX+wjyCyYrhuuJmiZaqZOBkS81W7zC8VVfKMTzcYgcIJTN82u1hXyffp3mgL/9w3hu85JjOlK1VuqaSG3AdB04t89/1O/w1cDnyilFU=')
handler = WebhookHandler('39fe11eaed2e9f91e5f54b6fd07cd785')

temperature = 0
weight = 0

@app.route('/dispender', methods=['GET'])
def dispender():
    global temperature, weight
    try:
        temperature = request.args.get('temperature')
        weight = request.args.get('weight')
    except:
        print('Args not correct')
    return 'OK'

@app.route("/callback", methods=['POST'])
def callback():
    # get X-Line-Signature header value
    signature = request.headers['X-Line-Signature']

    # get request body as text
    body = request.get_data(as_text=True)
    app.logger.info("Request body: " + body)

    # handle webhook body
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        print("Invalid signature. Please check your channel access token/channel secret.")
        abort(400)

    return 'OK'


@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    global temperature, weight
    if event.message.text == 'info':
        msg = 'temperature: {}\nweight: {}'.format(temperature, weight)
    else:
        msg = 'type \"info\" to get the information of the drink !'

    line_bot_api.reply_message(
        event.reply_token,
        TextSendMessage(text=msg))


if __name__ == "__main__":
    app.run()
