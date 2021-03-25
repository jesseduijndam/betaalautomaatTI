class Tekst{
    tekst : HTMLElement
    
    constructor(x : number, y : number, scale : number, txt : string){
        this.tekst = document.createElement("tekst")
            document.body.appendChild(this.tekst)
            this.tekst.id = "tekst"
            this.tekst.innerHTML = txt
            this.tekst.style.transform = `translate(${x}px, ${y}px) scale(${scale})`
    }
}   