(()=>{var e={298:e=>{"use strict";e.exports=require("electron")}},r={};function n(o){var t=r[o];if(void 0!==t)return t.exports;var i=r[o]={exports:{}};return e[o](i,i.exports,n),i.exports}n.ab=__dirname+"/native_modules/",(()=>{const{contextBridge:e}=n(298),{ipcRenderer:r}=n(298);e.exposeInMainWorld("ipc",{sendAsync:(e,...n)=>r.invoke(e,...n),on:(e,n)=>{r.on(e,((e,...r)=>n(...r)))}})})()})();
//# sourceMappingURL=preload.js.map