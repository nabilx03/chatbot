const api = {
    output: null,
    receiveInput(message) {
        api.output = "API respond"
        api.sendOutput();
    },
    sendOutput() {
        main.sendBotMessage(api.output);
    }
};