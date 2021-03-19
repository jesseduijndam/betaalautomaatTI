class AutomaatGui{
    protected main : Main
    public currentscreen : any
    private title : Tekst
    constructor(m : Main){
        this.main = m
        let title = document.createElement("title")
        title.innerHTML = "automaat"
        document.head.appendChild(title)
        let background = document.createElement("automaatbackground")
        document.body.appendChild(background)
        this.title = new Tekst(320,5,1,"welcome bij C5")
        let option1 = new Tekst(350,220,1,"scan pas")

    }
    protected aScan(){
        document.body.innerHTML = ""
        this.currentscreen = new aScan(this)
    }
    public update() {

    }
}
