class OnlineGui{
    protected main : Main
    constructor(m : Main){
        this.main = m
        let title = document.createElement("title")
        title.innerHTML = "online"
        document.head.appendChild(title)
        let background = document.createElement("onlinebackground")
        document.body.appendChild(background)

    }

    public update() {

    }
}