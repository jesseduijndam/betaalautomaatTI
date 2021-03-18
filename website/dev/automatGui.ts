class AutomaatGui{
    protected main : Main
    public currentscreen : any
    constructor(m : Main){
        this.main = m
        let title = document.createElement("title")
        title.innerHTML = "automaat"
        document.head.appendChild(title)
        let background = document.createElement("automaatbackground")
        document.body.appendChild(background)

    }

    public update() {

    }
}
