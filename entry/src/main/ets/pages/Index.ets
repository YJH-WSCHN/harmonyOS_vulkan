import { run } from 'libentry.so'

// Index.ets
@Entry
@Component
struct Index {
  build() {
    Column() {
      Text('Hello')
        .fontSize(30)
        .fontColor(Color.Red)
      XComponent({
        id: 'xcomponentId',
        type: 'surface',
        libraryname: 'entry'
      })
        .onLoad(()=>{
          run()
        })
        .margin({ bottom: 20 })
        .width(360)
        .height(360)
    }
  }
}