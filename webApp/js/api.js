const api = {
    input: null,
    output: null,
    dictionary: [
        ["geht", "gehts", "hallo", "dir", "mir"],
        ["öffne", "öffnen", "google", "internet", "kamera", "telefon"],
        ["nein", "nicht", "nö"],
        ["wetter", "heute", "morgen", "gestern", "vorgestern", "übermorgen", "mittag", "abend"]
    ],
    receiveInput(message) {
        api.input = message;
        api.analyseMsg();
        api.sendOutput();
    },
    analyseMsg() {
        let words = api.message.split(" ");
        words.forEach((el, ix, arr)=> {
            api.dictionary.forEach((el2, ix2, arr2)=> {
                
            });
        });
    },
    sendOutput() {
        api.output = "API respond";
        main.sendBotMessage(api.output);
    }
};