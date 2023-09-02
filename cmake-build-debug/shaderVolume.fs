#version 330 core

uniform sampler3D ourTexture;

uniform vec3 VolumePosition;
uniform vec3 VolumeScale;
uniform vec3 VolumeDivisions;

uniform mat4 RayTransform;
uniform vec2 WindowSize;
uniform vec3 CameraPosition;


in vec4 gl_FragCoord;

in vec3 percentPosition;
in vec3 position;
in float dist;

out vec4 FragColor;


vec3 direction;
vec3 lastCell = vec3(-1,-1,-1);

float far = 0;
float near = 0;

vec3 toPercentPos(vec3 pos){
    return (pos - VolumePosition) / VolumeScale;
}

vec4 layerColors(vec4 b, vec4 a){
    vec4 output;
    output.w = a.w + b.w * (1 - a.w);
    if(output.w == 0){
        return output;
    }
    output.xyz = (a.xyz * a.w + b.xyz * b.w * (1-a.w)) / output.w;
    return output;
}

bool isInVolume(vec3 point){
    point = toPercentPos(point);
    return all(greaterThanEqual(point, vec3(0, 0, 0)) && lessThanEqual(point, vec3(1, 1, 1)));
}

void findIntersections(){
    vec3 lowerBound = VolumePosition;
    vec3 upperBound = lowerBound + VolumeScale;

    float tmin = (lowerBound.x - CameraPosition.x) / direction.x;
    float tmax = (upperBound.x - CameraPosition.x) / direction.x;

    if (tmin > tmax){
        float temp = tmin;
        tmin = tmax;
        tmax = temp;
    }


    float tymin = (lowerBound.y - CameraPosition.y) / direction.y;
    float tymax = (upperBound.y - CameraPosition.y) / direction.y;

    if (tymin > tymax){
        float temp = tymin;
        tymin = tymax;
        tymax = temp;
    }

    /*
    //in theory it cannot get here
    if ((tmin > tymax) || (tymin > tmax)){
        return false;
    }
    */


    if (tymin > tmin){
        tmin = tymin;
    }


    if (tymax < tmax){
        tmax = tymax;
    }


    float tzmin = (lowerBound.z - CameraPosition.z) / direction.z;
    float tzmax = (upperBound.z - CameraPosition.z) / direction.z;

    if (tzmin > tzmax){
        float temp = tzmin;
        tzmin = tzmax;
        tzmax = temp;
    }

    /*
    //in theory it cannot get here
    if ((tmin > tzmax) || (tzmin > tmax)){
        return false;
    }
    */


    if (tzmin > tmin){
        tmin = tzmin;
    }

    if (tzmax < tmax){
        tmax = tzmax;
    }

    far = tmax - 0.00001;
    near = max(tmin + 0.00001, 0.0);
}

vec3 getCell(vec3 point){
    return floor(toPercentPos(point) * VolumeDivisions);
}

void main()
{
    direction = vec3(gl_FragCoord.x / WindowSize.x, 0.5, gl_FragCoord.y / WindowSize.y) - vec3(0.5, 0, 0.5);
    direction /= length(direction);//now it is a unit vector
    direction = vec3(RayTransform * vec4(direction, 1));
    findIntersections();
    vec4 color;



    vec3 farCell = getCell(CameraPosition + direction * far);
    vec3 nearCell = getCell(CameraPosition + direction * near);
    vec3 diff = abs(farCell - nearCell);
    float cells = max(diff.x + diff.y + diff.z, 1);

    float maxDist = length(VolumeScale);

    for(float i = 1; i >= 0.1/maxDist; i /= 1.02){
        float d = i * far + (1 - i) * near;
        vec3 pos = CameraPosition + direction * d;
        vec3 cell = getCell(pos);
        if(cell != lastCell){
            vec4 temp = texture(ourTexture, toPercentPos(pos));
            color = layerColors(color, temp);
            lastCell = cell;
        }
    }
    //for(float i = 1; i >= 0.001; i -= 0.001){
    //    float d = i * far + (1 - i) * near;
    //    vec3 pos = CameraPosition + direction * d;
    //    vec3 cell = getCell(pos);
    //    if(cell != lastCell){
    //        vec4 temp = texture(ourTexture, toPercentPos(pos));
    //        color = layerColors(color, temp);
    //        lastCell = cell;
    //    }
    //}
    vec3 pos = CameraPosition + direction * near;
    vec3 cell = getCell(pos);
    if(cell != lastCell){
        vec4 temp = texture(ourTexture, toPercentPos(pos));
        color = layerColors(color, temp);
        lastCell = cell;
    }

    //for(float i = distance; i >= 0; i -= delta){
    //    vec4 temp = texture(ourTexture, toPercentPos(CameraPosition + direction * i));
    //    color = layerColors(color, temp);
    //}
    FragColor = color;
    //FragColor = texture(ourTexture, toPercentPos(CameraPosition + direction * (distance)));
    //FragColor = vec4(abs((CameraPosition + direction * distance) - position), 1);
}