package personal.vankhulup.synthbridge

import android.content.res.AssetManager
import android.os.Bundle
import android.view.MotionEvent
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.wrapContentHeight
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.Modifier
import androidx.compose.ui.input.pointer.motionEventSpy
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.tooling.preview.Preview
import personal.vankhulup.synthbridge.ui.theme.SynthBridgeTheme

class MainActivity : ComponentActivity() {
  @OptIn(ExperimentalComposeUiApi::class)
  override fun onCreate(savedInstanceState: Bundle?) {
    super.onCreate(savedInstanceState)
    startEngine(assets)
    setContent {
      SynthBridgeTheme {
        // A surface container using the 'background' color from the theme
        Surface(modifier = Modifier.fillMaxSize(), color = MaterialTheme.colorScheme.background) {
          Button(modifier = Modifier
            .wrapContentSize() ,
            onClick = { tap(true)}) {
            Text(text = "Play something")
          }
        }
      }
    }
  }

  override fun onStop() {
    super.onStop()
    stopEngine()
  }

  companion object {
    init {
      System.loadLibrary("native-bridge")
    }
  }

  external fun startEngine(assetManager: AssetManager)
  external fun stopEngine()
  external fun tap(isNoteOn: Boolean)
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
  Text(
    text = "Hello $name!",
    modifier = modifier
  )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
  SynthBridgeTheme {
    Greeting("Android")
  }
}
