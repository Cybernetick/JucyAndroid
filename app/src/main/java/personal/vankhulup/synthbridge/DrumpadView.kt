package personal.vankhulup.synthbridge

import androidx.compose.animation.core.LinearEasing
import androidx.compose.animation.core.RepeatMode
import androidx.compose.animation.core.animateFloat
import androidx.compose.animation.core.infiniteRepeatable
import androidx.compose.animation.core.rememberInfiniteTransition
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.shape.CornerSize
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Checkbox
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.geometry.center
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import java.util.concurrent.TimeUnit

@Composable
@Preview
fun DrumpadView() {
    var checked by remember {
        mutableStateOf(true)
    }
    Box {
        Column(
            modifier =
                Modifier
                    .fillMaxSize()
                    .background(Color.Blue),
        ) {
            val infiniteTransition = rememberInfiniteTransition(label = "chrono")
            val offset by infiniteTransition.animateFloat(
                initialValue = 0f,
                targetValue = 1f,
                animationSpec =
                    infiniteRepeatable(
                        animation = tween(TimeUnit.SECONDS.toMillis(5).toInt(), delayMillis = 0, easing = LinearEasing),
                        repeatMode = RepeatMode.Restart,
                    ),
                label = "chronoOffset",
            )
            Canvas(
                modifier =
                    Modifier
                        .fillMaxSize()
                        .background(Color.Cyan)
                        .padding(horizontal = 10.dp)
                        .weight(1f),
            ) {
                drawChronometerBar()
                drawBtmBars()
                drawChronometerProgressIndicator(offset)
            }
            Row(
                modifier =
                    Modifier
                        .fillMaxWidth()
                        .background(Color.Yellow)
                        .height(200.dp),
                horizontalArrangement = Arrangement.SpaceAround,
                verticalAlignment = Alignment.CenterVertically,
            ) {
                Spacer(modifier = Modifier.width(12.dp))
                DrumpadButton(modifier = Modifier.weight(1f))
                Spacer(modifier = Modifier.width(12.dp))
                DrumpadButton(modifier = Modifier.weight(1f))
                Spacer(modifier = Modifier.width(12.dp))
                DrumpadButton(modifier = Modifier.weight(1f))
                Spacer(modifier = Modifier.width(12.dp))
                DrumpadButton(modifier = Modifier.weight(1f))
                Spacer(modifier = Modifier.width(12.dp))
            }
        }
        Row(
            modifier =
                Modifier
                    .wrapContentSize()
                    .align(Alignment.TopEnd),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            Text(text = "Metronome")
            Checkbox(checked = checked, onCheckedChange = {
                checked = it
            })
        }
    }
}

private fun DrawScope.drawChronometerBar() =
    drawLine(
        color = Color.Red,
        strokeWidth = 10f,
        start = Offset(x = 0f, y = size.center.y),
        end = Offset(x = size.width, y = size.center.y),
    )

private fun DrawScope.drawChronometerProgressIndicator(offset: Float) =
    drawLine(
        color = Color.Red,
        strokeWidth = 10f,
        start =
            Offset(
                x =
                    size.width * offset,
                y = size.center.y - 40,
            ),
        end = Offset(x = size.width * offset, y = size.center.y + 40),
    )

private fun DrawScope.drawBtmBars() {
    val quadrantSize = size / 4f
    drawCircle(Color.Red, radius = 10f, center = Offset(x = 5f, y = this.center.y))
    drawCircle(Color.Red, radius = 10f, center = Offset(x = quadrantSize.width + 5f, y = this.center.y))
    drawCircle(Color.Red, radius = 10f, center = Offset(x = 2 * quadrantSize.width + 5f, y = this.center.y))
    drawCircle(Color.Red, radius = 10f, center = Offset(x = 3 * quadrantSize.width + 5f, y = this.center.y))
}

@Composable
@Preview(widthDp = 120, heightDp = 120)
fun DrumpadButton(modifier: Modifier = Modifier) {
    Box(
        modifier =
            modifier
                .aspectRatio(1f)
                .fillMaxSize()
                .clip(RoundedCornerShape(corner = CornerSize(8.dp)))
                .clickable { }
                .background(Color.Red),
    )
}
