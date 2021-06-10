"use strict";
class AutomaatGui {
    constructor(m) {
        this.main = m;
        let title = document.createElement("title");
        title.innerHTML = "automaat";
        document.head.appendChild(title);
        let background = document.createElement("automaatbackground");
        document.body.appendChild(background);
        this.title = new Tekst(320, 5, 1, "welcome bij C5");
        let option1 = new Tekst(350, 220, 1, "scan pas");
    }
    aScan() {
        document.body.innerHTML = "";
        this.currentscreen = new aScan(this);
    }
    update() {
    }
}
class Main {
    constructor() {
        this.automaatGui();
        this.mainLoop();
    }
    mainLoop() {
        this.currentgui.update();
        requestAnimationFrame(() => this.mainLoop());
    }
    automaatGui() {
        document.body.innerHTML = "";
        this.currentgui = new AutomaatGui(this);
    }
    onlineGui() {
        document.body.innerHTML = "";
        this.currentgui = new OnlineGui(this);
    }
}
window.addEventListener("load", () => new Main());
class OnlineGui {
    constructor(m) {
        this.main = m;
        let title = document.createElement("title");
        title.innerHTML = "online";
        document.head.appendChild(title);
        let background = document.createElement("onlinebackground");
        document.body.appendChild(background);
    }
    update() {
    }
}
class Tekst {
    constructor(x, y, scale, txt) {
        this.tekst = document.createElement("tekst");
        document.body.appendChild(this.tekst);
        this.tekst.id = "tekst";
        this.tekst.innerHTML = txt;
        this.tekst.style.transform = `translate(${x}px, ${y}px) scale(${scale})`;
    }
}
//# sourceMappingURL=main.js.map