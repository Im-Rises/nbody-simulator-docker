import yaml
import argparse

def generate_docker_compose(total_particles, num_containers, time_simulation):
    services = {}

    for i in range(num_containers):
        cmd_argument_debut = i * total_particles / num_containers
        cmd_argument_fin = (i + 1) * total_particles / num_containers
        service_name = f"particulecalculator_{i}"

        service = {
            "build": {
                "context": "./src/NBodyCalculator",  # dossier de l'image
                "dockerfile": "Dockerfile"
            },
            "links": ["api"],
            "network_mode": "bridge",
            "environment": {
                "FIRSTINDEX": str(int(cmd_argument_debut)),
                "LASTINDEX": str(int(cmd_argument_fin))
            },
            "volumes": {
                "./src/dependencies/": "/nbody/dependencies/"
            }
        }

        services[service_name] = service


    services["api"] = generate_service_api(total_particles)
    services["redis"] = generate_service_redis()
    services["opengl"] = generate_service_opengl(total_particles, time_simulation)

    docker_compose = {
        "version": "3",
        "services": services
    }

    with open("docker-compose.yml", "w") as file:
        yaml.dump(docker_compose, file)



def generate_service_api(total_particles):
    api = {
        'build': {
            'context': './docker/api',
            'dockerfile': 'Dockerfile'
        },
        'restart': 'unless-stopped',
        'network_mode': 'bridge',
        'environment': [
            f'NB_PARTICULES={total_particles}',
        ],
        'command': "/bin/sh -c 'nodemon -e js,html index.js'",
        'ports': [
            '8080:9000'
        ],
        'links': [
            'redis'
        ]
    }
    return api

def generate_service_redis():
    redis = {
        'image': 'redis:6.2-alpine',
        'restart': 'unless-stopped',
        'network_mode': 'bridge',
        'expose': ['6379'],
    }
    return redis

def generate_service_opengl(total_particles, time_simulation):
    build_data = {
        'context': './src/NBodyGraphics',  # dossier de l'image
        'dockerfile': 'Dockerfile'
    }

    service = {
        'build': build_data,
        'network_mode': 'bridge',
        'environment': [
            f'NB_PARTICULES={total_particles}',
            f'TIME_SIMULATION={time_simulation}'
        ],
        'links': ['api'],
        'volumes': [
            './src/dependencies/:/nbody/dependencies/',
            './src/NBodyGraphics/output_dir/:/nbody/output_dir/'
        ]
    }
    return service



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("total_particles", type=int, help="Total number of particles")
    parser.add_argument("num_containers", type=int, help="Number of parallel Docker containers")
    parser.add_argument("time_simulation", type=float, help="Time of the simulation")
    args = parser.parse_args()

    generate_docker_compose(args.total_particles, args.num_containers, args.time_simulation)