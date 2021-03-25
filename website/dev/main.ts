class Main{
    public currentgui : any
    
    constructor() {
        this.automaatGui()
        this.mainLoop()
    }

    public mainLoop() : void{
        this.currentgui.update()
        requestAnimationFrame(() => this.mainLoop())
    }

    public automaatGui() {
        document.body.innerHTML = ""
        this.currentgui = new AutomaatGui(this)
    }

    public onlineGui() {
        document.body.innerHTML = ""
        this.currentgui = new OnlineGui(this)
    }
}

window.addEventListener("load",() => new Main())