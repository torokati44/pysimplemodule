//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;


network Net
{
    @display("bgb=652,358");
    submodules:
        pySimpleModule: PySimpleModule {
            @display("p=299,70");
        }
        source: Source {
            @display("p=85,239");
        }
        pyClassifier: PyClassifier {
            @display("p=275,239");
        }
        sink: Sink {
            @display("p=432,178");
        }
        sink1: Sink {
            @display("p=425,278");
        }
    connections:
        source.out --> pyClassifier.in;
        pyClassifier.out++ --> sink.in++;
        pyClassifier.out++ --> sink1.in++;
}
