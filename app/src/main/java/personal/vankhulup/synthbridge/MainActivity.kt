package personal.vankhulup.synthbridge

import android.content.res.AssetManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import personal.vankhulup.synthbridge.ui.theme.SynthBridgeTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        startEngine(assets)
        setContent {
            SynthBridgeTheme {
                // A surface container using the 'background' color from the theme
                Surface(modifier = Modifier.fillMaxSize(), color = MaterialTheme.colorScheme.background) {
                    DrumpadView()
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
fun Greeting(
    name: String,
    modifier: Modifier = Modifier,
) {
    Text(
        text = "Hello $name!",
        modifier = modifier,
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    SynthBridgeTheme {
        Greeting("Android")
    }
}
