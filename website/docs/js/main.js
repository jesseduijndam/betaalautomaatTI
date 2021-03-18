"use strict";
class AutomaatGui {
    constructor(m) {
        this.main = m;
        let title = document.createElement("title");
        title.innerHTML = "automaat";
        document.head.appendChild(title);
        let background = document.createElement("automaatbackground");
        document.body.appendChild(background);
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
//# sourceMappingURL=main.js.map