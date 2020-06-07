const main = {
    initialize() {
        main.profilePic();
        main.submit();
    },
    profilePic: function() {
        let $image = $("div.profile_pic");
        let height = $image.children("img").height(),    
            width = $image.children("img").width();
        let value = height > width ? height : width;
    },
    submit() {
        $("footer.keyboard input").keypress((event)=> {
            if(event.keyCode === 13) {
                main.sendUserMessage();
            }
        });
        $("footer.keyboard img").on("click", ()=> {
            main.sendUserMessage();
        });
    },
    getMsgTemplate(author, content) {
        return `<div id="${author}Msg">
                    <p>${content}</p>
                </div>`;
    },
    sendUserMessage() {
        let $input = $("footer.keyboard input");
        let message = $input.val();
        if(message.trim() == "") return;
        messageHTML = main.getMsgTemplate("user", message);
        $input.focus().val("");
        $("div.chat").append(messageHTML);
        api.receiveInput(message);
        //Android.toastMessage("Message send sucessfully");
    },
    sendBotMessage(message) {
        messageHTML = main.getMsgTemplate("bot", message);        
        $("div.chat").append(messageHTML);
    }
}